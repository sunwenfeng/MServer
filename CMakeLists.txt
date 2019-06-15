cmake_minimum_required(VERSION 3.6)
project(MServer)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp EventLoop.cpp EventLoop.h Socket.cpp Socket.h Channel.cpp Channel.h TcpServer.cpp TcpServer.h Acceptor.cpp Acceptor.h TcpConnection.cpp TcpConnection.h Epoller.cpp Epoller.h)
add_executable(MServer ${SOURCE_FILES})