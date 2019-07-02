//
// Created by sun on 19-6-26.
//

#ifndef MSERVER_BUFFER_H
#define MSERVER_BUFFER_H


#include <vector>
#include <iostream>

#define BUFFERSIZE 1024
class Buffer {
public:
    Buffer():AL_Buffer(BUFFERSIZE),readIndex(0),writeIndex(0){}
    ~Buffer(){
        std::cout<<"Buffer closed"<<std::endl;
    }

    int readData(int fd,int &error);
    void printData(int len);

    void append(const char*,int len);   //将长度为len的char加入到Buffer的后面

    void updateBufferIndex(int len);    //write了Buffer中的len长度之后，更新Buffer的readIndex和writeIndex

    int dataSize(){
        return writeIndex-readIndex;
    }
    const char* dataBegin(){//返回当前Buffer中存在数据的最开始的位置
        return static_cast<const char*>(&*AL_Buffer.begin()) + readIndex;
    }

private:
    std::vector<char> AL_Buffer;
    int readIndex;
    int writeIndex;                 //Buffer中的数据区间为[readIndex,writeIndex)
};


#endif //MSERVER_BUFFER_H
