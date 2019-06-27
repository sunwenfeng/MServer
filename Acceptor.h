//
// Created by sun on 19-6-15.
//

#ifndef MSERVER_ACCEPTOR_H
#define MSERVER_ACCEPTOR_H


#include <functional>
#include "Socket.h"
#include "Channel.h"

class Acceptor {
public:
    typedef std::function<void(int,struct sockaddr_in)> AcceptorCallback;

    Acceptor(EventLoop* loop,uint16_t port);
    ~Acceptor(){
        std::cout<<"Acceptor closed"<<std::endl;
    }

    void start();

    void handleReadEvent();

    void setAcceptorNewConnectionCallback(AcceptorCallback callback){
        newConnectionCallback = callback;
    }

private:
    Socket acceptfd;                                //监听socket
    Channel acceptorChannel;                        //负责acceptfd IO的channel
    AcceptorCallback newConnectionCallback;         //listen之后调用的回调函数,进行accept及后续操作

};


#endif //MSERVER_ACCEPTOR_H
