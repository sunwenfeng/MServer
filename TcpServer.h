//
// Created by sun on 19-6-15.
//

#ifndef MSERVER_TCPSERVER_H
#define MSERVER_TCPSERVER_H


#include <memory>
#include <map>
#include "Acceptor.h"
#include "TcpConnection.h"

/*
 * TcpServer用于建立服务器，管理监听描述符和已连接描述符
 *
 * */
class TcpServer {
public:
    TcpServer(){}
    ~TcpServer(){}

    int start();

private:
    std::unique_ptr<Acceptor> Acceptor_;
    std::map<int,TcpConnetionPtr> ConnectionMap;     //描述符和对应的TcpConnection对象

};


#endif //MSERVER_TCPSERVER_H
