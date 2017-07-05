#ifndef SRC_IREQUESTSERVER_H
#define SRC_IREQUESTSERVER_H

class IRequestServer {
public:
    IRequestServer() {};
    virtual ~IRequestServer() {};
    IRequestServer(const IRequestServer&) = delete;
    IRequestServer& operator=(const IRequestServer&) = delete;

    virtual void start() = 0;
};

#endif //SRC_IREQUESTSERVER_H
