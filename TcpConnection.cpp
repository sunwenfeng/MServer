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
    auto function1 = std::bind(&TcpConnection::handleWrite,this);
    tcpConnectionChannel_->setChannelWriteCallback(function1);
}

void TcpConnection::addConnToEvents() {
    tcpConnectionChannel_->addReadToEvents();       //目前只监听read
}

void TcpConnection::handleRead() {//描述符可读，需要读数据然后处理

    int error;

    int ret = InputBuffer.readData(tcpConnectionChannel_->get_fd(),error);

    if(ret == 0){
        std::cout<<std::endl<<"******************************************"<<std::endl;
        std::cout<<"connection begin close" <<std::endl;             //客户端关闭

        //此时TcpConnection::tcpConnectionChannel_中的fa_events即关心事件不为空，是否有必要清空？？

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
        std::cout<<strerror(error)<<std::endl;
    }
}

void TcpConnection::send(std::string &msg) {
    int writeLen = 0;
    int msgSize = msg.size();
    if(OutputBuffer.dataSize() == 0){
        //输出缓冲中没有数据，不存在乱序问题，直接write，否则必须将这部分数据添加到缓冲区末尾，待前面的数据发送之后才能发送这部分数据
        writeLen = write(tcpConnectionChannel_->get_fd(),msg.data(),msg.size());
        if(writeLen >= 0){
            if(writeLen == msgSize){
                std::cout<<"All is send to peer"<<std::endl;
                return;
            }

            else{
                std::cout<<"Remain message need send to peer"<<std::endl;
                //将剩下的数据添加到输出Buffer的尾部，等待Epoll唤醒发送
            }
        }
        else{// write error，需要将全部数据加到Buffer的尾部
            writeLen = 0;
            std::cout<<"write error : ";
            std::cout<<strerror(errno)<<std::endl;
        }
        std::cout<<"append remain data to outputBuffer and addWriteToEvents"<<std::endl;
        OutputBuffer.append(static_cast<const char*>(msg)+writeLen,(msgSize-writeLen));//append参数的第一个参数为开始位置，第二个参数为从开始位置之后的长度
        tcpConnectionChannel_->addWriteToEvents();
    }
}
void TcpConnection::handleWrite() {//Epoll激活之后发送缓冲区中的数据，每个Tcp连接都有一个TcpConnection管理的OIutputBuffer，write即可
    int writeLen = write(tcpConnectionChannel_->get_fd(),OutputBuffer.dataBegin(),OutputBuffer.dataSize());
    if(writeLen >= 0){
        //从OutputBuffer中写了writlen个长度，则需要更新OutputBuffer中readIndex和writeIndex
        OutputBuffer.updateBufferIndex(writeLen);
        if(OutputBuffer.dataSize() == 0){
            tcpConnectionChannel_->removeWriteEvents();
            std::cout<<"connection "<<tcpConnectionChannel_->get_fd()<<" removeWriteEvents"<<std::endl;
        }
    }
    else{
        std::cout<<"handleWrite error : ";
        std::cout<<strerror(errno)<<std::endl;
    }

}



