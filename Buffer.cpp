//
// Created by sun on 19-6-26.
//

#include <sys/uio.h>
#include "Buffer.h"
int Buffer::readData(int fd) {
    char extraBuffer[65536];

    struct iovec iov[2];
    iov[0].iov_base = &*AL_Buffer.begin();
    iov[0].iov_len = BUFFERSIZE;
    iov[1].iov_base = extraBuffer;
    iov[1].iov_len = 65536;

    int readLen = readv(fd,iov,2); //依次写入AL_Buffer和extraBuffer两个缓冲区。

    if(readLen <= 0){
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
