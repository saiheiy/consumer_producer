#include <SessionManager.h>
//#include <TestParser.h>
#include <JsonParser.h>
#include <StdinStringProcessor.h>
#include <Application.h>
#include "TestRequestServer.h"


int main(){
    SessionManager in_sessionManager;
    //TestParser in_testParser;
    JsonParser in_parser;
    StdinStringProcessor in_stdStringProcessor(in_sessionManager, in_parser);

    Application app(in_sessionManager, in_stdStringProcessor);
    TestRequestServer testRS(in_sessionManager);
    app.addRequestServer(&testRS);

    app.run();
    return 0;
}
