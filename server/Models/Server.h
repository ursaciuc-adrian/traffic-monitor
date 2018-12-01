#pragma once

#include <netinet/in.h>
#include <unistd.h>
#include <vector>
#include <string>

#include "Client.h"

class Server
{
private:
    struct sockaddr_in server;
    int socket;
    int nfds;
    fd_set master;

    void Listen(int queueSize);
    void Bind();

public:
    std::vector<Client *> clients;
    void Select(fd_set &masterCopy);

    explicit Server();
    void CreateServer(int port, int queueSize);
    int AddClient();
    void CloseClient(int id);
    void WriteToAllClients(std::string message, int exclude = 0);

    int GetSocket();

    ~Server();
};