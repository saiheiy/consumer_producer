#ifndef SRC_JSONPARSER_H
#define SRC_JSONPARSER_H

#include <IParser.h>
#include <JsonType.h>
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>
#include <string>

class JsonParser : public IParser<std::string> {
public:
    std::shared_ptr<IParsedType> parse(const std::string& toParse) override {
        return std::make_shared<JsonType>(toParse);
    }

};


#endif //SRC_JSONPARSER_H
