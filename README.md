# MServer
基于Reactor模式实现服务器，首先实现单线程Reactor，只关注网络socket事件，参考muduo的架构

### vision 1
参考muduo的架构完成了第一版，单线程reactor模式，能够处理读事件，接下来完善写事件，关闭连接，错误处理。  

分为三个部分：
* EventLoop和Epoller，服务器主循环，事件驱动器
* TcpServer和Acceptor/TcpConnection，管理TCP连接
* Channel，桥梁作用，将上面两部分连接起来
***

* RAII的方式管理socket套接字
* Epoll LT进行IO复用
* 回调函数保证类良好的封装性，减少类之间的耦合


