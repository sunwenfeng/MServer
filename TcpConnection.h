//
// Created by sun on 19-6-15.
//

#ifndef MSERVER_TCPCONNECTION_H
#define MSERVER_TCPCONNECTION_H

#include <memory>

#include "Socket.h"
#include "Channel.h"

class TcpConnection {
public:
    typedef std::function<void()> TcpConnectionCalback;

    TcpConnection(EventLoop* loop,int fd);
    ~TcpConnection();

    void handleRead();

    void addConnToEvents();

    void setTcpConnectionReadCalback(TcpConnectionCalback callback){
        TcpConnectionReadCalback = callback;
    }


private:
    std::unique_ptr<Socket> connectfd_;
    std::unique_ptr<Channel> tcpConnectionChannel_;

    TcpConnectionCalback TcpConnectionReadCalback;
};

extern typedef std::shared_ptr<TcpConnection> TcpConnetionPtr;

#endif //MSERVER_TCPCONNECTION_H
