#pragma once

#include <strings.h>

#include "../../Shared/CommunicationHelper.h"
#include "Server.h"
#include "Client.cpp"

void Server::createServer(int port, int queueSize)
{
    this->m_socket = CreateSocket();

    int optval = 1;
    setsockopt(this->m_socket, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));

    this->m_server.sin_family = AF_INET;
    this->m_server.sin_addr.s_addr = htonl(INADDR_ANY);
    this->m_server.sin_port = htons(static_cast<uint16_t>(port));

    this->m_bind();
    this->m_listen(queueSize);

    FD_SET(this->m_socket, &this->m_master);
    this->m_nfds = this->m_socket;

    std::cout << "The server started on port " << port << std::endl;
}

void Server::addClient()
{
    int socket = accept(this->m_socket, nullptr, nullptr);

    auto *client = new Client(socket, "127.0.0.1", 2026);
    this->m_clients.push_back(client);

    FD_SET(socket, &this->m_master);

    this->m_nfds = std::max(this->m_nfds, socket);

    std::cout << "#" << client->getSocket() <<" | A new client connected to the server." << std::endl;

    std::string welcomeMessage = "#" + std::to_string(client->getSocket()) + " | You are now connected to the server.";
    this->writeToClient(client, welcomeMessage);
}

void Server::removeClient(Client *client)
{
    int index = -1;
    for (int i = 0; i < this->m_clients.size(); ++i)
    {
        if(this->m_clients[i]->getSocket() == client->getSocket())
        {
            index = i;
            break;
        }
    }

    if(index != -1)
    {
        this->m_clients.erase(this->m_clients.begin() + index);

        close(client->getSocket());
        FD_CLR(client->getSocket(), &this->m_master);

        std::cout << "#" << client->getSocket() <<" | A client disconnected from the server." << std::endl;
    }
    else
    {
        // TODO: Handle error
    }
}

void Server::m_listen(int queueSize)
{
    if (listen(this->m_socket, queueSize) == -1)
    {
         perror("[Server]Error at listen().\n");
    }
}

void Server::m_bind()
{
    if (bind(this->m_socket, (struct sockaddr *) &this->m_server, sizeof(struct sockaddr)) == -1)
    {
        perror("[Server]Error at bind().\n");
    }
}

void Server::writeToAllClients(std::string message, int exclude)
{
    for (auto *client: this->m_clients)
    {
        if(client->getSocket() == exclude)
        {
            continue;
        }

        this->writeToClient(client, message);
    }
}

int Server::getSocket() const
{
    return this->m_socket;
}

Server::Server()
{
    bzero(&this->m_server, sizeof(this->m_server));
    FD_ZERO(&this->m_master);
}

void Server::select(fd_set &masterCopy)
{
    masterCopy = this->m_master;
    ::select(this->m_nfds + 1, &masterCopy, nullptr, nullptr, nullptr);
}

void Server::writeToClient(Client *client, std::string message)
{
    Write(client->getSocket(), message);
}

const std::vector<Client *> Server::getClients() const
{
    return this->m_clients;
}

Server::~Server()
= default;
