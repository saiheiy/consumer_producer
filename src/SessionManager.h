#ifndef SRC_SESSIONMANAGER_H
#define SRC_SESSIONMANAGER_H

#include <ISession.h>
#include <IParsedType.h>
#include <TestSession.h>
#include <SynchronizedQueue.h>
#include <Constants.h>
#include <conpro_types.h>
#include <bslmt_lockguard.h>
#include <bslmt_mutex.h>
#include <bslmt_condition.h>
#include <bdlmt_threadpool.h>
#include <bslmt_threadattributes.h>
#include <string>
#include <unordered_map>
#include <memory>
#include <iostream>
#include <thread>
#include <stdexcept>
#include <cassert>

using namespace BloombergLP;

class SessionManager {
public:
    SessionManager()
        :m_threadpool(m_threadattributes, Constants::SM_MIN_THREADS,
                      Constants::SM_MAX_THREADS, Constants::SM_MAX_IDLETIME)
    {}

    void start(){
        //add test session TODO:  remove later
        //addSession(TestSession::createSession(Constants::TEST_CLIENTID1));

        setIsRunning(true);
        if(0 != m_threadpool.start()){
            throw std::runtime_error("SessionManager: failed to start threadpool");
        }
        m_smThread = std::thread(&SessionManager::listenForUpdates, this);
    }

    void addSession(const std::shared_ptr<ISession>& sessPtr) {
        bslmt::LockGuard<bslmt::Mutex> guard(&m_sessionMap_mutex);
        //there should not be duplicate ClientId's being added
        assert(m_sessionsMap.find(sessPtr->clientId()) == m_sessionsMap.end());
        m_sessionsMap[sessPtr->clientId()] = sessPtr;
        std::cout << "session: " << sessPtr->clientId() << std::endl;
    }

    void addJob(const ClientId& cid, const std::shared_ptr<IParsedType>& job){
        if(m_sessionsMap.find(cid) == m_sessionsMap.end()){
            std::cerr << "ISession with Clientid: " << cid << "does not exist.\n";
            return;
        }
        std::shared_ptr<ISession>& sess_ptr = m_sessionsMap.at(cid);
        bool wasEmpty = sess_ptr->addJob(job);
        if(wasEmpty){
            m_sessionsToProcessQueue.enqueue(cid);
            m_cv.signal();
        }
    }

    void setIsRunning(bool state) noexcept {
        isRunning = state;
    }


    ~SessionManager() {
        setIsRunning(false);
        if(m_smThread.joinable()){
            m_smThread.join();
        }
    }

    SessionManager(const SessionManager&) = delete;
    SessionManager& operator=(const SessionManager&) = delete;


private:
    void listenForUpdates(){
        std::cout << "SessionManager: listening for updates\n";
        while(isRunning){
            {
                bslmt::LockGuard<bslmt::Mutex> guard(&m_cv_mutex);
                while(m_sessionsToProcessQueue.empty()) {
                    m_cv.wait(&m_cv_mutex);
                }
            }
            const ClientId& cid = m_sessionsToProcessQueue.front();
            assert(m_sessionsMap.find(cid) != m_sessionsMap.end());
            std::shared_ptr<ISession>& sessPtr = m_sessionsMap.at(cid);
            if (sessPtr->inProgress()) {
                m_sessionsToProcessQueue.rotateOne();
            }
            else {
                m_threadpool.enqueueJob(bdlf::BindUtil::bind(&ISession::processJobs,
                                                             sessPtr.get()));
                m_sessionsToProcessQueue.dequeue();
            }
        }
    }

    std::thread m_smThread;
    bslmt::ThreadAttributes m_threadattributes;
    bdlmt::ThreadPool m_threadpool;
    bslmt::Mutex m_sessionMap_mutex;
    bslmt::Mutex m_cv_mutex;
    bslmt::Condition m_cv;
    std::unordered_map<ClientId, std::shared_ptr<ISession>> m_sessionsMap;
    SynchronizedQueue<ClientId> m_sessionsToProcessQueue;
    std::atomic_bool isRunning{false};
};


#endif //SRC_SESSIONMANAGER_H
