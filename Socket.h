//
// Created by sun on 19-6-15.
//

#ifndef MSERVER_SOCKET_H
#define MSERVER_SOCKET_H

#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <iostream>

/*
 * 用RAII的方式管理socket套接字，用socket对象管理socket的读写操作，并且在析构函数中关闭socket
 * */
class Socket {
public:
    Socket(){
        socketfd = socket(PF_INET,SOCK_STREAM | SOCK_NONBLOCK | SOCK_CLOEXEC,0);
        //创建一个非阻塞Socket
        if(socketfd < 0)
            std::cout<<"socket() error"<<std::endl;
    }
    Socket(int fd):socketfd(fd){}

    ~Socket(){
        close(socketfd);
    }

    int getSocketfd(){
        return socketfd;
    }
    int Bind(uint16_t port) const;
    int Listen() const;
    int Accept(struct sockaddr_in *client) const;

    int Connect()const ;                            //connect是客户端函数，暂未实现

private:
    int socketfd;                                   //管理的socket套接字描述符
};


#endif //MSERVER_SOCKET_H
