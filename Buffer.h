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

private:
    std::vector<char> AL_Buffer;
    int readIndex;
    int writeIndex;
};


#endif //MSERVER_BUFFER_H
