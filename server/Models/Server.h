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
    std::vector<Client *> clients;

    int socket;
    int nfds;
    fd_set master;

    void Listen(int queueSize);
    void Bind();

public:
    explicit Server();
    void CreateServer(int port, int queueSize);
    void Select(fd_set &masterCopy);

    void AddClient();
    void RemoveClient(Client *client);

    void WriteToAllClients(std::string message, int exclude = 0);
    void WriteToClient(Client *client, std::string message);

    int GetSocket();
    const std::vector<Client *> GetClients();

    ~Server();
};