//
// Created by Sai Hei Yeung on 6/24/17.
//

#ifndef SRC_SESSION_H
#define SRC_SESSION_H

#include <ISession.h>
#include <conpro_types.h>
#include <bslmt_lockguard.h>
#include <bslmt_mutex.h>
#include <vector>
#include <memory>
#include <atomic>
#include <iostream>



using namespace BloombergLP;

class TestSession : public ISession {
public:
    TestSession(const ClientId& cid)
        :m_cid(cid)
    {}

    static std::shared_ptr<TestSession> createSession(const ClientId& cid){
        return std::make_shared<TestSession>(cid);
        //TODO call this and SessionManager::addSession in main.
    }

    bool addJob(const std::shared_ptr<Parsed> &job) override {
        //add job and signal if queue went from empty to non-empty
        bslmt::LockGuard<bslmt::Mutex> guard(&m_sessionMutex);
        bool wasEmpty = jobs_queued.empty();
        jobs_queued.emplace_back(job);
        return wasEmpty;
    }

    void processJobs() {
        {
            bslmt::LockGuard<bslmt::Mutex> guard(&m_sessionMutex);
            std::swap(jobs_in_progress, jobs_queued);
        }

        for (const auto& pptr: jobs_in_progress){
            std::cout << "TestSession: processing : "
                      << *pptr << "\n";
        }
    }

    const ClientId& clientId() const {
        return m_cid;
    }

    const bool inProgress() const {
        return m_inProgress;
    }

private:
    ClientId m_cid;
    bslmt::Mutex m_sessionMutex;
    std::vector<std::shared_ptr<Parsed>> jobs_in_progress;
    std::vector<std::shared_ptr<Parsed>> jobs_queued;
    std::atomic_bool m_inProgress{false};

};


#endif //SRC_SESSION_H
