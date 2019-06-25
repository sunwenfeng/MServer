# MServer
基于Reactor模式实现服务器，首先实现单线程Reactor，只关注网络socket事件，参考muduo的架构
***
一个channel负责一个描述符的IO，而一个EventLoop中可以执行多个描述符的IO，也就会有多个就绪的channel  
使用回调函数使得代码逻辑更加清晰，TcpServer，Acceptor，Channel，TcpConnection


