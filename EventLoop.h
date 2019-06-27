//
// Created by sun on 19-6-15.
//

#ifndef MSERVER_EVENTLOOP_H
#define MSERVER_EVENTLOOP_H

#include <vector>
#include <memory>
#include "Channel.h"
#include "Epoller.h"

/*
 * 事件驱动器，每个线程对应一个
 *
 * */
class EventLoop {
public:
    EventLoop():epoll(new Epoller()){
        activeChannels.clear();
    }
    ~EventLoop();

    int loop();

    int updateEvents(Channel* channel);   //channel::update调用

private:
    std::unique_ptr<Epoller> epoll;
    std::vector<Channel*> activeChannels;  //由Epoller返回就绪的channel
};


#endif //MSERVER_EVENTLOOP_H
