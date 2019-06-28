//
// Created by sun on 19-6-15.
//

#include <iostream>
#include "Epoller.h"
int Epoller::poller(std::vector<Channel*> &activeChannels) {
    // epoll描述符将监听的socket和对应的事件存储在一颗红黑树上，所以不需要单独的数据结构来保存epoll监听的套接字
    // 而epoll_wait会将就绪的描述符和事件以（struct epoll）返回

    int ret = epoll_wait(epollfd,&*epoll_revents.begin(),epoll_revents.size(),EPOLL_WAIT_TIME);//vector的迭代器是普通指针，取首元素的地址付给struct epoll_events*
    if(ret<0)
        std::cout<<"epoll_wait error"<<std::endl;

    for(int i=0;i<ret;i++){
        int active_fd = epoll_revents[i].data.fd;  //就绪事件的描述符
        Channel* active_Channel = ChannelMap[active_fd];
        active_Channel->set_fd_revents(epoll_revents[i].events);
        activeChannels.push_back(active_Channel);
    }

    return ret;
}
/*
 * 新建acceptor之后，需要将监听描述符加入到Poller监听，但acceptor不知道Poller，需要channel转接，channel和poller同属一个EventLoop，但互相
 * 不知道对方，所以需要EventLoop()转接
 * */

int Epoller::epoll_updateEvents(Channel *channel) { //EventLoop::updateEvents调用
    //更新ChannelMap以及监听事件
    int fd_ = channel->get_fd();
    if(ChannelMap.find(channel->get_fd()) != ChannelMap.end()){ //已经有这个描述符，只需要更新fd关心的events
        struct epoll_event ev;
        ev.events = channel->get_fd_events();
        ev.data.fd = fd_;
        int ret = epoll_ctl(epollfd,EPOLL_CTL_MOD,fd_,&ev);
        if(ret < 0)
            std::cout<<"epoll_mod error"<<std::endl;
        return ret;
    }
    else{//找不到这个描述符，所以需要将这个描述符对应的channel加入ChannelMap;并将这个fd加入Epoll
        ChannelMap[fd_] = channel;
        struct epoll_event ev;
        ev.events = channel->get_fd_events();
        ev.data.fd = fd_;

        std::cout<<fd_<<" mod epoll"<<std::endl;

        int ret = epoll_ctl(epollfd,EPOLL_CTL_ADD,fd_,&ev);
        if(ret < 0)
            std::cout<<"epoll_add error" <<std::endl;
        return ret;
    }

}

int Epoller::epoll_removeEvents(Channel *channel) {
    int fd_ = channel->get_fd();
    ChannelMap.erase(fd_);
    struct epoll_event ev;
    ev.events = channel->get_fd_events();
    ev.data.fd = fd_;
    int ret = epoll_ctl(epollfd,EPOLL_CTL_DEL,fd_,&ev);
    if(ret < 0){
        std::cout<<"epoll_del error" <<std::endl;
    }
    std::cout<<"epoll_del " <<fd_<<std::endl;
    return ret;
}