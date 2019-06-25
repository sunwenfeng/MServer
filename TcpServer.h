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
    typedef std::function<void()> TcpServerCallback;

    TcpServer(EventLoop* loop,uint16_t port){}
    ~TcpServer(){}

    int start();

    void newConnection(const int connfd,const struct addr_in clientAddr);   //TcpServer在接受一个新连接之后执行的动作，传递给Acceptor的回调函数调用

private:
    EventLoop* loop;
    std::unique_ptr<Acceptor> Acceptor_;             //加后缀下划线表明是智能指针
    std::map<int,TcpConnetionPtr> ConnectionMap;     //描述符和对应的TcpConnection对象

    TcpServerCallback connectionCallback;            //建立新连接之后的回调函数，一般打印客户端信息
    TcpServerCallback TcpServerReadCallback;         //业务逻辑处理

};


#endif //MSERVER_TCPSERVER_H
