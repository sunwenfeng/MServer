# MServer
基于Reactor模式实现服务器，首先实现单线程Reactor，只关注网络socket事件，参考muduo的架构

### version 1
参考muduo的架构完成了第一版，单线程reactor模式，能够处理读事件，接下来完善写事件，关闭连接，错误处理。  

分为三个部分：
* EventLoop和Epoller，服务器主循环，事件驱动器
* TcpServer和Acceptor/TcpConnection，管理TCP连接
* Channel，桥梁作用，将上面两部分连接起来
***

* RAII的方式管理socket套接字
* Epoll LT进行IO复用
* 回调函数保证类良好的封装性，减少类之间的耦合

### version 2
完善了关闭连接以及错误处理，但都比较简单。    

当read返回0时表明客户端关闭了连接，则服务器关闭该套接字的连接，两个工作：
* 通知Epoller将该套接字的监听事件删除，由channel通知Epoller
* 通知TcpServer将管理该套接字的TcpConnection从ConnectionMap中删除，并析构TcpConnection对象。TcpConnection析构时，其类成员Buffer，Channel，Socket类也会析构。由于类Socket通过RAII的方式管理socket套接字，类Socket析构时socket套接字也被关闭，关闭工作完成。
* 由于是已连接套接字的工作，所以在TcpConnection类中进行，TcpConnection的生命期由TcpServer控制，TcpConnection是TcpServer的类成员，上一条的通知工作由回调函数来完成。
  
 错误处理使用strerror将读套接字时的错误进行输出。


### version 3
完善写事件的处理，还需要考虑的是如果关闭连接和写事件冲突时的处理。

服务器发送数据时，首先尝试一次性将所有的数据发送完毕，如果不能全部发送，则将剩余的数据写入到输出Buffer中，并将该描述符的写事件加入到Epoll的监听事件中。  
然后等待Epoll监听写事件，写就绪之后，handlewrite进行处理，一旦数据发送完毕，则将该描述符的写事件从Epoll的监听事件中移除。避免busy loop。
