#pragma once

#include <string>
#include <netinet/in.h>

class Server
{
public:
    Server(std::string ip, int port);
    struct sockaddr_in server;

};
