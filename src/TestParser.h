#ifndef SRC_TESTPARSER_H
#define SRC_TESTPARSER_H

#include <conpro_types.h>
#include <IParser.h>
#include <TestParsedType.h>
#include <IParsedType.h>
#include <Constants.h>
#include <memory>
#include <string>

class TestParser : public IParser<std::string> {
public:
    std::shared_ptr<IParsedType> parse(const std::string& toParse) override {
        ClientId cid = Constants::TEST_CLIENTID1;
        return std::make_shared<TestParsedType>(cid, toParse);
    }
};



#endif //SRC_TESTPARSER_H
