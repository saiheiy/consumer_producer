#ifndef SRC_APPLICATION_H
#define SRC_APPLICATION_H

#include <InputProcessor.h>
#include <SessionManager.h>
#include <TestSession.h>
#include <string>
#include <iostream>

class Application {
public:
    Application(SessionManager& in_sessionManager, InputProcessor& in_inputProcessor)
            :m_sessionManager(in_sessionManager),
            m_inputProcessor(in_inputProcessor)
    {}

    void run(){
        m_sessionManager.start();
        m_inputProcessor.runMainLoop();
    }

private:
    SessionManager& m_sessionManager;
    InputProcessor& m_inputProcessor;
};


//TODO:  make classes noncopyable, nonmovable
//TODO:  add virtual destructors
//TODO:  look up when to add noexcept



#endif //SRC_APPLICATION_H
