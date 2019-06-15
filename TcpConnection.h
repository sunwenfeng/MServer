//
// Created by sun on 19-6-15.
//

#ifndef MSERVER_TCPCONNECTION_H
#define MSERVER_TCPCONNECTION_H

#include <memory>

#include "Socket.h"

class TcpConnection {
public:

private:
    std::unique_ptr<Socket> connectfd;
};

extern typedef std::shared_ptr<TcpConnection> TcpConnetionPtr;

#endif //MSERVER_TCPCONNECTION_H
