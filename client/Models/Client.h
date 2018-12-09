#pragma once

#include <string>
#include "Server.h"

class Client
{
    int m_socket;
    fd_set m_master;

public:
    explicit Client(int socket);
    void connectToServer(Server *server);

    void select(fd_set &masterCopy);
    void close();

    int getSocket() const;
};

