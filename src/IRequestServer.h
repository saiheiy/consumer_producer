#ifndef SRC_IREQUESTSERVER_H
#define SRC_IREQUESTSERVER_H

#include <vector>
#include <memory>

class IRequestServer {
public:
    IRequestServer() {};
    virtual ~IRequestServer() {};
    IRequestServer(const IRequestServer&) = delete;
    IRequestServer& operator=(const IRequestServer&) = delete;

    virtual void start() = 0;
    virtual void batchProcessJobs(const std::vector<std::shared_ptr<IParsedType>>&) = 0;
};

#endif //SRC_IREQUESTSERVER_H
