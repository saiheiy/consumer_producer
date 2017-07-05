//
// Created by Sai Hei Yeung on 6/22/17.
//

#ifndef SRC_INPUTPROCESSOR_H
#define SRC_INPUTPROCESSOR_H

#include <Constants.h>
#include <SessionManager.h>
#include <IMessageProcessor.h>
#include <IParser.h>
#include <IParsedType.h>
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

class StdinStringProcessor : public IMessageProcessor {
public:
    StdinStringProcessor(SessionManager& in_sessionManager, IParser<std::string>& in_parser)
    :m_sessionManager(in_sessionManager),
     m_parser(in_parser),
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
        std::shared_ptr<IParsedType> job = m_parser.parse(line);
        m_sessionManager.addJob(job->getClientId(), job);
    }

    void runMainLoop() override {
        std::string line;
        while(std::cin >> line){
            m_threadpool.enqueueJob(bdlf::BindUtil::bind(&StdinStringProcessor::runParseInput, this, line));
        }
    }

    ~StdinStringProcessor() override {
        if(m_threadpool.enabled()) {
            m_threadpool.stop();
        }
    }

    StdinStringProcessor(const StdinStringProcessor&) = delete;
    StdinStringProcessor& operator=(const StdinStringProcessor&) = delete;

private:
    SessionManager& m_sessionManager;
    IParser<std::string>& m_parser;
    bslmt::ThreadAttributes m_threadattributes;
    bdlmt::ThreadPool m_threadpool;
};


#endif //SRC_INPUTPROCESSOR_H
