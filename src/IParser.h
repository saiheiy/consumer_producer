#ifndef SRC_IPARSER_H
#define SRC_IPARSER_H

#include <memory>
#include <IParsedType.h>

template <typename T>
class IParser {
public:
    IParser() {};
    virtual ~IParser() {};
    IParser(const IParser&) = delete;
    IParser& operator=(const IParser&) = delete;

    virtual std::shared_ptr<IParsedType> parse(const T& toParse) = 0;
};

#endif //SRC_IPARSER_H
