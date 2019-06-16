//
// Created by sun on 19-6-15.
//

#ifndef MSERVER_EPOLLER_H
#define MSERVER_EPOLLER_H

/*
 * 通过epoll进行IO复用，Epoll封装epoll的相关操作。是EventLoop的成员
 *
 * */
#include <sys/epoll.h>
#include <vector>
#include <map>
#include "Channel.h"

const int MAXEVENTS = 4096;             //epoll_wait最多能监听的事件数
const int EPOLL_WAIT_TIME = 10000;      //epoll_wait的超时事件，ms

class Epoller {
public:
    Epoller():epollfd(epoll_create(1)),epoll_revents(MAXEVENTS){    }
    ~Epoller(){}

    int poller(std::vector<Channel*>& activeChannels);  //就就绪的IO对应的Channel加入activeChannels，供EventLoop使用

    int epoll_updateEvents(Channel* channel);

private:
    int epollfd;  //epoll文件描述符
    //事件就绪后，需要通过channel进行事件的处理，而epoll_wait只会返回就绪的描述符，需要通过描述符找到对应的channel，需要下面这个map
    std::map<int,Channel*> ChannelMap;
    std::vector<struct epoll_event> epoll_revents; //epoll_wait返回的就绪事件列表,大小为MAXEVENTS
};


#endif //MSERVER_EPOLLER_H
