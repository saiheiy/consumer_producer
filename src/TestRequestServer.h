#ifndef SRC_TESTREQUESTSERVER_H
#define SRC_TESTREQUESTSERVER_H

#include <PT.h>
#include <IRequestServer.h>
#include <SessionManager.h>
#include <TestSession.h>
#include <Constants.h>
#include <vector>
#include <memory>

class TestRequestServer: public IRequestServer {
public:
    TestRequestServer(SessionManager& in_sessionManager)
        :m_sessionManager(in_sessionManager)
    {}

    void start() override {
        m_sessionManager.addSession(TestSession::createSession(Constants::TEST_CLIENTID1, this));
        m_sessionManager.addSession(TestSession::createSession(Constants::TEST_CLIENTID2, this));
        m_sessionManager.addSession(TestSession::createSession(Constants::TEST_CLIENTID3, this));
    }

    void batchProcessJobs(const std::vector<std::shared_ptr<IParsedType>>& jobsToProcess) override {
        for (const auto& pptr: jobsToProcess) {
            PT() << "TestRequestServer:  processing: " << *pptr << "\n";
        }
    }

private:
    SessionManager& m_sessionManager;
};

#endif //SRC_TESTREQUESTSERVER_H
