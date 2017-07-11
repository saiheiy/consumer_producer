//
// Created by Sai Hei Yeung on 6/24/17.
//

#ifndef SRC_SESSION_H
#define SRC_SESSION_H

#include <ISession.h>
#include <IParsedType.h>
#include <IRequestServer.h>
#include <conpro_types.h>
#include <PT.h>
#include <bslmt_lockguard.h>
#include <bslmt_mutex.h>
#include <vector>
#include <memory>
#include <atomic>
#include <iostream>



using namespace BloombergLP;

class TestSession : public ISession {
public:
    TestSession(const ClientId& cid, IRequestServer* respPtr)
        :m_cid(cid),
         m_respPtr(respPtr)
    {}

    static std::shared_ptr<TestSession> createSession(const ClientId& cid, IRequestServer* resp){
        return std::make_shared<TestSession>(cid, resp);
    }

    bool addJob(const std::shared_ptr<IParsedType> &job) override {
        //add job and signal if queue went from empty to non-empty
        PT() << __func__ << "-> " << *job << "\n";
        bslmt::LockGuard<bslmt::Mutex> guard(&m_sessionMutex);
        bool wasEmpty = jobs_queued.empty();
        jobs_queued.emplace_back(job);
        return wasEmpty;
    }

    void processJobs() override {
        {
            bslmt::LockGuard<bslmt::Mutex> guard(&m_sessionMutex);
            std::swap(jobs_in_progress, jobs_queued);
            m_inProgress = true;
        }


//        for (const auto& pptr: jobs_in_progress) {
//            PT() << "HERE TestSession: processing : "
//                      << *pptr << "\n";
//        }
        m_respPtr->batchProcessJobs(jobs_in_progress);

        //clear jobs_in_progress when finished
        jobs_in_progress.clear();
        m_inProgress = false;
    }

    const ClientId& clientId() const {
        return m_cid;
    }

    const bool inProgress() const {
        return m_inProgress;
    }

private:
    ClientId m_cid;
    IRequestServer* m_respPtr;
    bslmt::Mutex m_sessionMutex;
    std::vector<std::shared_ptr<IParsedType>> jobs_in_progress;
    std::vector<std::shared_ptr<IParsedType>> jobs_queued;
    std::atomic_bool m_inProgress{false};

};


#endif //SRC_SESSION_H
