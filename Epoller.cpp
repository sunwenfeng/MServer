//
// Created by sun on 19-6-15.
//

#include "Epoller.h"
int Epoller::poller(std::vector<Channel*>& activeChannel) {
    // epoll描述符将监听的socket和对应的事件存储在一颗红黑树上，所以不需要单独的数据结构来保存epoll监听的套接字
    // 而epoll_wait会将就绪的描述符和事件以（struct epoll）返回

    int ret = epoll_wait(epollfd,epoll_revents,epoll_revents.size(),)
}

int Epoller::update_events() {

    epoll_ctl();


}