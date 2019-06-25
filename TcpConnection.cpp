//
// Created by sun on 19-6-15.
//

#include "TcpConnection.h"

TcpConnection::TcpConnection(EventLoop *loop, int fd)
        :connectfd_(new Socket(fd)),
         tcpConnectionChannel_(new Channel(loop,fd))
{
    tcpConnectionChannel_->setReadCallback(&TcpConnection::handleRead,this);
}

void TcpConnection::addConnToEvents() {
    tcpConnectionChannel_->addReadToEvents();       //目前只监听read
}

void TcpConnection::handleRead() {//描述符可读，需要读数据然后处理

}



