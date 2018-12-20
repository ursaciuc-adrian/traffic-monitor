#pragma once

#include <sys/socket.h>
#include <netinet/in.h>

class Client
{
    int m_socket;
    std::string m_ip;
    int m_port;
    int m_speed;

public:
    Client(int socket, std::string ip, int port);
    int getSocket();

    void setSpeed(int speed);

    ~Client();
};