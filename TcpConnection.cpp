//
// Created by sun on 19-6-15.
//

#include <iostream>
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

    int ret = InputBuffer.readData(tcpConnectionChannel_->get_fd());

    if(ret == 0){
        std::cout<<"connection closed" <<std::endl;
        //还应该将描述符从Epoll中去除
    }
    else{
        std::cout<<"read data"<<std::endl;
        TcpConnectionReadCalback();   //业务逻辑处理
    }
}



