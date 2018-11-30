#pragma once

#include <sys/socket.h>
#include <netinet/in.h>

class Client
{
    int id;
    struct sockaddr_in from;
    socklen_t length;

public:
    Client(int id, sockaddr_in from, socklen_t length);
    int GetId();

    ~Client();
};