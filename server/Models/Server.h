#pragma once

#include <netinet/in.h>
#include <unistd.h>
#include <vector>
#include <string>

#include "Client.h"

class Server
{
private:
    std::vector<Client *> clients;
    struct sockaddr_in server;
    int socket;

    void Listen(int queueSize);
    void Bind();

public:
    explicit Server(int socket, int port, int queueSize);
    int AddClient();
    void CloseClient(int id);
    void WriteToAllClients(std::string message);

    ~Server();
};