#ifndef SRC_ISESSION_H
#define SRC_ISESSION_H

#include <conpro_types.h>
#include <IParsedType.h>
#include <atomic>


class ISession {
public:
    virtual bool addJob(const std::shared_ptr<IParsedType> &job) = 0;

    virtual void processJobs() = 0;

    virtual const ClientId& clientId() const = 0;

    virtual const bool inProgress() const  = 0;

    virtual ~ISession() {};
};

#endif //SRC_ISESSION_H
