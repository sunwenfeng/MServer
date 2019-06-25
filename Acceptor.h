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
    typedef std::function<void(const int ,const struct addr_in)> AcceptorCallback;

    Acceptor(EventLoop* loop,uint16_t port);
    ~Acceptor();

    void start();

    void handleReadEvent();

    void setNewConnectionCallback(AcceptorCallback callback){
        newConnectionCallback = callback;
    }

private:
    Socket acceptfd;                                //监听socket
    Channel acceptorChannel;                        //负责acceptfd IO的channel
    AcceptorCallback newConnectionCallback;         //listen之后调用的回调函数

};


#endif //MSERVER_ACCEPTOR_H
