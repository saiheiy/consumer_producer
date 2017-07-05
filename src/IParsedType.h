#ifndef SRC_IPARSEDTYPE_H
#define SRC_IPARSEDTYPE_H

#include <string>

class IParsedType {
public:
    IParsedType() {};
    virtual ~IParsedType() {};

    virtual const ClientId& getClientId() const = 0;

    virtual std::ostream &write(std::ostream &dest) const = 0;
};

std::ostream &operator<<(std::ostream &os, const IParsedType &in_obj){
    return in_obj.write(os);
}


#endif //SRC_IPARSEDTYPE_H
