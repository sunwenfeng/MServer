//
// Created by sun on 19-7-2.
//

#ifndef MSERVER_CALLBACK_H
#define MSERVER_CALLBACK_H

#endif //MSERVER_CALLBACK_H

#include "TcpConnection.h"

class Callback{
    typedef std::function<void(const TcpConnetionPtr&,Buffer*)> TcpServerCallback;
};
