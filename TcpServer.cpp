//
// Created by sun on 19-6-15.
//

#include "TcpServer.h"
#include <functional>
#include <arpa/inet.h>
#include <iostream>

TcpServer::TcpServer(EventLoop* loop_,uint16_t port)
        :Acceptor_(new Acceptor(loop_,port)),
         loop(loop_)
{
    Acceptor_->setNewConnectionCallback(std::bind(&TcpServer::newConnection,this,std::placeholders::_1,std::placeholders::_2));
}

void TcpServer::newConnection(const int connfd,const struct addr_in clientAddr ) {

    std::cout<<"Received TCP connection from"<<inet_ntoa(clientAddr.sin_addr)<<": "<<ntohs(clientAddr.sin_port)<<std::endl;

    TcpConnetionPtr newconn(new TcpConnection(loop,connfd));
    newconn->setTcpConnectionReadCalback(TcpServerReadCallback);

    ConnectionMap[connfd] = newconn;

    //定义TcpConnection对象管理新连接，之后就要将将这个已建立描述符号加入Epoller的关注列表中
    newconn->addConnToEvents();
}
