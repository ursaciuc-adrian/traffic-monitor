#pragma once

#include <sys/socket.h>
#include <netinet/in.h>

class Client
{
    int socket;
    std::string ip;
    int port;
public:
    Client(int socket, std::string ip, int port);
    int GetSocket();

    ~Client();
};