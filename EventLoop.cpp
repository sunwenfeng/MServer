//
// Created by sun on 19-6-15.
//

#include <iostream>
#include "EventLoop.h"

EventLoop::~EventLoop() {}

int EventLoop::updateEvents(Channel *channel) {
    epoll->epoll_updateEvents(channel);
}

int EventLoop::loop() {
    while(1){
        activeChannels.clear();
        int ret = epoll->poller(activeChannels);
        if(ret < 0){
            std::cout<<"epoll_poller error"<<std::endl;
            continue;
        }
        std::vector<Channel*>::iterator it = activeChannels.begin();
        for(it=activeChannels.begin();it!=activeChannels.end();++it){
            Channel* channel_ = *it;
            channel_->handleEvents();
            //std::cout<<channel_->get_fd()<<" is ready"<<std::endl;
        }
    }
}
