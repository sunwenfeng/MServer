//
// Created by sun on 19-6-15.
//

#include <sys/epoll.h>
#include <iostream>
#include "Channel.h"
#include "EventLoop.h"

Channel::Channel(EventLoop* loop_,int fd_):loop(loop_),fd(fd_) {}

Channel::~Channel() {
    std::cout<<"Channel closed"<<std::endl;
}

void Channel::addReadToEvents() {
    fd_events |= EPOLLIN;          //先更新自己的关心事件，这样更新EPoller的时候，直接从这个地方看应该关心哪些事件
    updateEvents();
}

void Channel::updateEvents() {     //目前只考虑了读.写需要再考虑
    loop->updateEvents(this);
}

void Channel::removeEvents() {
    loop->removeEvents(this);
}

int Channel::handleEvents() {
    if(fd_revents & EPOLLIN){
        std::cout<<std::endl<<"fd "<<fd<<" read events"<<std::endl;
        readCallback();
    }
}
