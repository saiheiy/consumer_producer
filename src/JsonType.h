#ifndef SRC_JSONTYPE_H
#define SRC_JSONTYPE_H

#include <IParsedType.h>
#include <conpro_types.h>
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>
#include <string>
#include <iostream>


class JsonType : public IParsedType {
public:
    JsonType(const std::string& toParse)
    {
        d.Parse(toParse.c_str());
        m_cid = d["clientId"].GetString();
    }

    const ClientId& getClientId() const {
        return m_cid;
    }

    std::ostream& write(std::ostream& dest) const override {
        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        d.Accept(writer);
        return dest << getClientId() << ":" << buffer.GetString();
    }

private:
    rapidjson::Document d;
    ClientId m_cid;
};


#endif //SRC_JSONTYPE_H
