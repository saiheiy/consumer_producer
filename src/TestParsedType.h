#ifndef SRC_TESTPARSEDTYPE_H
#define SRC_TESTPARSEDTYPE_H

#include <conpro_types.h>
#include <IParsedType.h>
#include <string>

class TestParsedType : public IParsedType {
public:
    TestParsedType(const ClientId& in_cid, const std::string& in_str)
        :m_data(in_str),
         m_cid(in_cid)
    {}

    const ClientId& getClientId() const override {
        return m_cid;
    }

    std::ostream &write(std::ostream &dest) const override {
        return dest << m_cid << ": " << m_data;
    }

private:
    std::string m_data;
    ClientId m_cid;
};

#endif //SRC_TESTPARSEDTYPE_H
