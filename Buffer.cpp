//
// Created by sun on 19-6-26.
//

#include <sys/uio.h>
#include "Buffer.h"
int Buffer::readData(int fd,int& error) {
    char extraBuffer[65536];

    struct iovec iov[2];
    iov[0].iov_base = &*AL_Buffer.begin();
    iov[0].iov_len = BUFFERSIZE;
    iov[1].iov_base = extraBuffer;
    iov[1].iov_len = 65536;

    int readLen = readv(fd,iov,2); //依次写入AL_Buffer和extraBuffer两个缓冲区。

    if(readLen <= 0){   //成功返回读写字节数，出错返回-1,对方关闭返回0
        //std::cout<<"errno is "<<errno;
        error = errno;
        return  readLen;
    }

    //接下来将extraBuffer的数据加入到AL_Buffer
    if((readLen + writeIndex)<= AL_Buffer.size()){   //没有用到extraBuffer
        writeIndex += readLen;
        return readLen;
    }
    else{
        // AL_Buffer的剩余空间不够用了

        int freeSize = readIndex;
        int extraSize = readLen - (AL_Buffer.size() - writeIndex);
        writeIndex = AL_Buffer.size();

        //在writeIndex后找出足够的空间

        if(freeSize > extraSize){
            std::copy(AL_Buffer.begin()+readIndex,AL_Buffer.begin()+writeIndex,AL_Buffer.begin());
            readIndex = 0;
            writeIndex = writeIndex - readIndex;
        }
        else{
            AL_Buffer.resize(AL_Buffer.size() + extraSize);
        }

        // 最后再把extraBuffer的内容添加到AL_Buffer的后面
        std::copy(extraBuffer,extraBuffer+extraSize,AL_Buffer.begin()+writeIndex);

        return readLen;
    }

}

void Buffer::printData(int len) {
    for(int i=0;i<len;i++){
        std::cout<<AL_Buffer[i];
    }
    std::cout<<std::endl;
}

void Buffer::append(const char* str,int len) {    //将长为len的str添加到Buffer的后面，如果空间不够，则移动Buffer的内容，或者给Buffer扩容
    int freeSizeAfterWriteIndex =  AL_Buffer.size() - writeIndex;
    int freeSizeBeforeReadIndex = readIndex;

    if(freeSizeAfterWriteIndex <= len){
        std::copy(str,str+len,AL_Buffer.begin()+writeIndex);
        writeIndex += len;
        return;
    }
    else{
        std::copy(AL_Buffer.begin()+readIndex,AL_Buffer.begin()+writeIndex,AL_Buffer.begin()); //先把所有的数据移动到Buffer的头部
        readIndex = 0;
        writeIndex = writeIndex-readIndex;

        if(freeSizeAfterWriteIndex + freeSizeBeforeReadIndex <= len){  //Buffer的空间能放下，直接加到后面
            std::copy(str,str+len,AL_Buffer.begin()+writeIndex);
            writeIndex += len;
            return;
        }

        else{//Buffer的空间不够用，则扩容，然后将数据加到Buffer后面
            AL_Buffer.resize(writeIndex-readIndex+len);
            std::copy(str,str+len,AL_Buffer.begin()+writeIndex);
            return ;
        }
    }
}

void Buffer::updateBufferIndex(int len) {
    readIndex += len;
    if(writeIndex == readIndex){        //Buffer中没有数据了
        readIndex = 0;
        writeIndex = 0;
    }
}

