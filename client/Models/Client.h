#pragma once

#include <string>
#include "Server.h"

class Client
{
    int m_socket;

public:
    explicit Client(int socket);
    void connectToServer(Server *server);

    int getSocket() const;
};

