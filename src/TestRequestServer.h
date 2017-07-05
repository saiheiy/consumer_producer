#ifndef SRC_TESTREQUESTSERVER_H
#define SRC_TESTREQUESTSERVER_H

#include <IRequestServer.h>
#include <SessionManager.h>
#include <TestSession.h>
#include <Constants.h>

class TestRequestServer: public IRequestServer {
public:
    TestRequestServer(SessionManager& in_sessionManager)
        :m_sessionManager(in_sessionManager)
    {}

    void start() override {
        m_sessionManager.addSession(TestSession::createSession(Constants::TEST_CLIENTID1));
        m_sessionManager.addSession(TestSession::createSession(Constants::TEST_CLIENTID2));
        m_sessionManager.addSession(TestSession::createSession(Constants::TEST_CLIENTID3));
    }

private:
    SessionManager& m_sessionManager;
};

#endif //SRC_TESTREQUESTSERVER_H
