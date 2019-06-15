//
// Created by sun on 19-6-15.
//

#ifndef MSERVER_CHANNEL_H
#define MSERVER_CHANNEL_H


class Channel {
public:
    Channel(){}
    ~Channel(){}

    int handleEvents();

private:
    // epoll检测到本描述符有事件就绪时，就将channel加入活动列表中，并调用channel::handleEvent()进行处理，、
    // 但由于一个描述符可能监听多个事件呢，通过revents来保存当前描述符的就绪事件
    struct epoll_event* fd_revents;

};


#endif //MSERVER_CHANNEL_H
