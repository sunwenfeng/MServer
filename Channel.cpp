//
// Created by sun on 19-6-15.
//

#include "Channel.h"

Channel::Channel(EventLoop* loop_,int fd_):loop(loop_),fd(fd_) {}

Channel::~Channel() {}

void Channel::addReadToEvents() {
    fd_events |= EPOLLIN;          //先更新自己的关心事件，这样更新EPoller的时候，直接从这个地方看应该关心哪些事件
    updateEvents();
}

void Channel::updateEvents() {     //目前只考虑了读，写，删除需要再考虑
    loop->updateEvents(this);
}

int Channel::handleEvents() {

}
