#include <iostream>
#include <functional>
#include "TcpServer.h"
#include "EventLoop.h"

void message(){
    std::cout<<"receive one message"<<std::endl;
    //write(5,"hello",sizeof("hello"));
}
/*
 * 现在有一个问题就是参考muduo的方式定义业务处理毁掉函数时出错，在目前的测试中虽然定义了回调函数，但在Tcp::connection的handlread中没有使用回调函数
 *
 *
 * */
int main() {
    EventLoop loop;
    TcpServer server(&loop,2008);
    server.setTcpServerReadCallback(std::bind(message));
    server.start();
    loop.loop();
    return 0;
}