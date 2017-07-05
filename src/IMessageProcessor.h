#ifndef SRC_IMESSAGEPROCESSOR_H
#define SRC_IMESSAGEPROCESSOR_H

using namespace BloombergLP;

class IMessageProcessor {
public:
    IMessageProcessor() {};
    virtual ~IMessageProcessor() {};
    IMessageProcessor(const IMessageProcessor&) = delete;
    IMessageProcessor& operator=(const IMessageProcessor&) = delete;

    virtual void runMainLoop() = 0;
};



#endif //SRC_IMESSAGEPROCESSOR_H
