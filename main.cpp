#include <iostream>
#include <functional>
#include "TcpServer.h"
#include "EventLoop.h"

void message(){
    std::cout<<"receive one message"<<std::endl;
    write(5,"hello",sizeof("hello"));
}
int main() {
    EventLoop loop;
    TcpServer server(&loop,2008);
    server.setTcpServerReadCallback(std::bind(message));
    server.start();
    loop.loop();

    return 0;
}