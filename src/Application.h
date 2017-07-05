#ifndef SRC_APPLICATION_H
#define SRC_APPLICATION_H

#include <IMessageProcessor.h>
#include <SessionManager.h>
#include <IRequestServer.h>
#include <string>
#include <iostream>

class Application {
public:
    Application(SessionManager& in_sessionManager, IMessageProcessor& in_msgProcessor)
            :m_sessionManager(in_sessionManager),
            m_msgProcessor(in_msgProcessor)
    {}

    void run(){
        m_sessionManager.start();
        for(auto rs_ptr: m_requestServerArr){
            rs_ptr->start();
        }
        m_msgProcessor.runMainLoop();
    }

    void addRequestServer(IRequestServer *rsptr){
        m_requestServerArr.emplace_back(rsptr);
    }

private:
    SessionManager& m_sessionManager;
    IMessageProcessor& m_msgProcessor;
    std::vector<IRequestServer *> m_requestServerArr;
};


//TODO:  make classes noncopyable, nonmovable
//TODO:  add virtual destructors
//TODO:  look up when to add noexcept



#endif //SRC_APPLICATION_H
