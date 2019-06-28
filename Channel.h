//
// Created by sun on 19-6-15.
//

#ifndef MSERVER_CHANNEL_H
#define MSERVER_CHANNEL_H

#include <functional>

class EventLoop;
/*
 * Channel需要通过EventLoop来通知Epoller更新监听事件，需要用到EventLoop的函数
 * EventLoop在Epoller监听到事件后，需要通过Channel来通知TcpServer，所以要用到Channel的函数
 * EventLoop和Channel是相互包含的关系，但在两个文件中互相include行不通
 *
 * 解决的方法：
 * 在EventLoop中include"channel"，在Channel中声明EventLoop，并且在类中定义EventLoop*
 * */

class Channel {
public:
    Channel(EventLoop* loop_,int fd_);
    ~Channel();

    typedef std::function<void()> ChannelCallback;

    int handleEvents();

    void addReadToEvents();             //更新自己对应的描述符的关心事件，并更新Epoller的关心事件
    void updateEvents();                //只处理添加和更新
    void removeEvents();                //处理事件删除

    int get_fd(){
        return fd;
    }
    u_int32_t get_fd_events(){
        return fd_events;
    }
    void setChannelReadCallback(ChannelCallback _callback){
        readCallback = _callback;
    }
    void set_fd_revents(u_int32_t fd_revents_){
        fd_revents = fd_revents_;
    }

private:

    u_int32_t fd_events;
    /* epoll检测到本描述符有事件就绪时，就将channel加入活动列表中，并调用channel::handleEvent()进行处理，、
    但由于一个描述符可能监听多个事件呢，通过events来保存当前描述符的关心的事件*/
    u_int32_t fd_revents;
    /*
     * 当fd有事件就绪后，需要知道哪些事件就绪，用revents保存
     * */

    const int fd;
    //channel负责描述符事件的分发，需要知道这个描述符，但并不拥有


    EventLoop* loop;
    /*还是上面的问题，channel需要更新Epoller的关心事件，但channel不知道Epoller，需要EventLoop的转接，所以需要EventLoop的指针
    此外，channel负责EventLoop和TcpConnection/Acceptor的转接，所以更需要知道EventLoop的指针*/

    ChannelCallback readCallback;

    ChannelCallback writeCallback;
    ChannelCallback closeCallback;
    /* channel的回调函数，在Acceptor和TcpConnection中绑定不同的函数*/

};

#endif //MSERVER_CHANNEL_H
