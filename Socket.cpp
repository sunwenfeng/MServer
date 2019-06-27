//
// Created by sun on 19-6-15.
//

#include <netinet/in.h>
#include <cstring>
#include <iostream>
#include "Socket.h"

int Socket::Bind(uint16_t port) const {
    //socket()只是指定了套接字描述副的地址组，但并没有指定具体的socket地址，需要用bind命名，对于client来说匿名即可，server需要指定
    struct sockaddr_in name;
    bzero(&name,sizeof(name));
    name.sin_family = AF_INET;                  //地址组
    name.sin_addr.s_addr  = htonl(INADDR_ANY);  //socket地址，内核分配
    name.sin_port = htons(port);
    int res =  bind(socketfd, reinterpret_cast<struct sockaddr*>(&name),sizeof(name));
    if(res < 0)
        std::cout<<"socket bind error"<<std::endl;
    return res;
}

int Socket::Listen() const {
    //默认创建的socket是主动套接字，需要将其设置为监听套接字
    int res = listen(socketfd,SOMAXCONN);
    if(res < 0)
        std::cout<<"socket listen() error"<<std::endl;
    return res;
}

int Socket::Accept(struct sockaddr_in *client) const {
    //accept接受客户端连接，返回已连接描述符，并通过client返回客户端地址
    socklen_t len = sizeof(struct sockaddr_in);
    int connfd = accept4(socketfd, reinterpret_cast<struct sockaddr*>(client),&len,SOCK_NONBLOCK | SOCK_CLOEXEC);//非阻塞accept，返回的connfd继承了SOCK_NONBLOCK | SOCK_CLOEXEC特性
    if(connfd < 0 ){
        std::cout<<"socket accept() error"<<std::endl;
    }
    return connfd;
}