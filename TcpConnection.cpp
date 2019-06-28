//
// Created by sun on 19-6-15.
//

#include <iostream>
#include <cstring>
#include "TcpConnection.h"

TcpConnection::TcpConnection(EventLoop *loop, int fd)
        :connectfd_(new Socket(fd)),
         tcpConnectionChannel_(new Channel(loop,fd))
{
    auto funtion = std::bind(&TcpConnection::handleRead,this);
    tcpConnectionChannel_->setChannelReadCallback(funtion);
}

void TcpConnection::addConnToEvents() {
    tcpConnectionChannel_->addReadToEvents();       //目前只监听read
}

void TcpConnection::handleRead() {//描述符可读，需要读数据然后处理

    int error;

    int ret = InputBuffer.readData(tcpConnectionChannel_->get_fd(),error);

    if(ret == 0){
        std::cout<<std::endl<<"******************************************"<<std::endl;
        std::cout<<"connection begin close" <<std::endl;
        //客户端关闭
        tcpConnectionChannel_->removeEvents();                      //将描述符从Epoll中去除
        TcpConnectionCloseCalback(tcpConnectionChannel_->get_fd()); //TcpServer::ConnectionMap中删除关闭的TcpConnetion，并将其析构
    }
    else if(ret > 0){
        std::cout<<"read data "<<ret<<std::endl;
        InputBuffer.printData(ret);
        TcpConnectionReadCalback();   //业务逻辑处理
    }
    else{
        std::cout<<"read error : ";
        std::cout<<strerror(error);
    }
}



