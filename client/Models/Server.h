#pragma once

#include <string>
#include <netinet/in.h>

class Server
{
    std::string m_ip;
    int m_port;

public:
    struct sockaddr_in server;

    Server(std::string ip, int port);
};
