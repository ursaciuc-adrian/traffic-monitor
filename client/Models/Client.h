#pragma once

#include <string>
#include "Server.h"

class Client
{
    int socket;
public:
    explicit Client(int socket);
    void ConnectToServer(Server *server);

    int GetSocket();
};

