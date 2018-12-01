#pragma once

#include <sys/socket.h>
#include <netinet/in.h>

using namespace std;

class Client
{
    int socket;
    string ip;
    int port;
public:
    Client(int socket, string ip, int port);
    int GetSocket();

    ~Client();
};