//
// Created by sun on 19-6-15.
//

#ifndef MSERVER_TCPCONNECTION_H
#define MSERVER_TCPCONNECTION_H

#include <memory>

#include "Socket.h"
#include "Channel.h"
#include "Buffer.h"

class TcpConnection {
public:
    typedef std::function<void()> TcpConnectionCalback;
    typedef std::function<void(int)> TcpCloseConnCalback;

    TcpConnection(EventLoop* loop,int fd);
    ~TcpConnection(){
        std::cout<<"TcpConnection closed"<<std::endl;
    }

    void handleRead();
    void handleWrite();
    void send(std::string & msg);

    void addConnToEvents();

    void setTcpConnectionReadCalback(TcpConnectionCalback callback){
        TcpConnectionReadCalback = callback;
    }
    void setTcpConnectionCloseCalback(TcpCloseConnCalback callback){
        TcpConnectionCloseCalback = callback;
    }
    int get_fd(){
        return tcpConnectionChannel_->get_fd();
    }

private:
    std::unique_ptr<Socket> connectfd_;
    std::unique_ptr<Channel> tcpConnectionChannel_;

    Buffer InputBuffer;
    Buffer OutputBuffer;

    TcpConnectionCalback TcpConnectionReadCalback;     //业务逻辑处理
    TcpCloseConnCalback TcpConnectionCloseCalback;     //关闭连接，通知TcpServer从map中删掉本TcpConnection

};

 typedef std::shared_ptr<TcpConnection> TcpConnetionPtr;

#endif //MSERVER_TCPCONNECTION_H
