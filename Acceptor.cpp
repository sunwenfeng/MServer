//
// Created by sun on 19-6-15.
//

#include <iostream>
#include <unistd.h>
#include <netinet/in.h>
#include "Acceptor.h"

Acceptor::Acceptor(EventLoop* loop,uint16_t port)
        :acceptfd(),
         acceptorChannel(loop,acceptfd.getSocketfd())
{
    acceptfd.Bind(port);
    acceptorChannel.setReadCallback(std::bind(&Acceptor::handleReadEvent,this)); //channel有多个callback，目前只设置acceptor的readcallback

}

void Acceptor::start() {//构造函数只是创建了主动套接字，将其转为监听套接字才真正开启服务器
    acceptfd.Listen();
    acceptorChannel.addReadToEvents();    //  将监听套接字的可写事件加入到Poller的关注
}

void Acceptor::handleReadEvent() {  //监听描述符可写之后，由channel通过回调函数调用handleReadEvent来处理，而监听描述符可写时，表明收到客户端连接

    struct sockaddr_in client;
    int connfd = acceptfd.Accept(&client);
    if(connfd < 0){
        std::cout<<"accept error"<<std::endl;
        //还应该进行一些其他的处理
    }
    else{
        newConnectionCallback();    //创建TcpConnection类来管理新连接，而Acceptor不知道TcpConnection的存在，通过回调函数让上层的TcpServer去创建TcpConnection对象
    }
}