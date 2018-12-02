#pragma once

#include <netinet/in.h>
#include <unistd.h>
#include <vector>
#include <string>

#include "Client.h"

class Server
{
private:
    struct sockaddr_in m_server;
    std::vector<Client *> m_clients;

    int m_socket;
    int m_nfds;
    fd_set m_master;

    void m_listen(int queueSize);
    void m_bind();

public:
    explicit Server();
    void createServer(int port, int queueSize);
    void select(fd_set &masterCopy);

    void addClient();
    void removeClient(Client *client);

    void writeToAllClients(std::string message, int exclude = 0);
    void writeToClient(Client *client, std::string message);

    int getSocket() const;
    const std::vector<Client *> getClients() const;

    ~Server();
};