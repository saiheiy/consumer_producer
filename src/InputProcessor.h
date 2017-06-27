//
// Created by Sai Hei Yeung on 6/22/17.
//

#ifndef SRC_INPUTPROCESSOR_H
#define SRC_INPUTPROCESSOR_H

#include <Constants.h>
#include <SessionManager.h>
#include <conpro_types.h>
#include <bdlmt_threadpool.h>
#include <bslmt_threadattributes.h>
#include <bdlf_bind.h>
#include <string>
#include <iostream>
#include <stdexcept>
#include <utility>
#include <memory>

using namespace BloombergLP;

class InputProcessor {
public:
    InputProcessor(SessionManager& in_sessionManager)
    :m_sessionManager(in_sessionManager),
     m_threadattributes(),
     m_threadpool(m_threadattributes, Constants::IP_MIN_THREADS,
                  Constants::IP_MAX_THREADS, Constants::IP_MAX_IDLETIME)
    {
        if(0 != m_threadpool.start()){
            throw std::runtime_error("Failed to start minimum number of threads");
        }
    }

    void runParseInput(const std::string& line) {
        std::cout << "Parsing " << line << std::endl;
        ClientId id = Constants::TEST_CLIENTID1;
        //create job
        std::shared_ptr<Parsed> job = std::make_shared<Parsed>(line);
        m_sessionManager.addJob(id, job);
    }

    void runMainLoop() {
        std::string line;
        while(std::cin >> line){
            m_threadpool.enqueueJob(bdlf::BindUtil::bind(&InputProcessor::runParseInput, this, line));
        }
    }

    ~InputProcessor() {
        if(m_threadpool.enabled()) {
            m_threadpool.stop();
        }
    }

    InputProcessor(const InputProcessor&) = delete;
    InputProcessor& operator=(const InputProcessor&) = delete;

private:
    SessionManager& m_sessionManager;
    bslmt::ThreadAttributes m_threadattributes;
    bdlmt::ThreadPool m_threadpool;
};


#endif //SRC_INPUTPROCESSOR_H
