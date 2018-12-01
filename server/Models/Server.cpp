#pragma once

#include <strings.h>
#include "../../Shared/CommunicationHelper.h"
#include "Server.h"
#include "Client.cpp"

void Server::CreateServer(int port, int queueSize)
{
    this->socket = CreateSocket();

    int optval = 1;
    setsockopt(this->socket, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));

    this->server.sin_family = AF_INET;
    this->server.sin_addr.s_addr = htonl(INADDR_ANY);
    this->server.sin_port = htons(static_cast<uint16_t>(port));

    this->Bind();
    this->Listen(queueSize);

    FD_SET(this->socket, &this->master);
    this->nfds = this->socket;
}

int Server::AddClient()
{
    int socket = accept(this->socket, nullptr, nullptr);

    auto *client = new Client(socket, "127.0.0.1", 2026);
    this->clients.push_back(client);

    FD_SET(socket, &this->master);

    this->nfds = max(this->nfds, socket);

    return socket;
}

void Server::CloseClient(int id)
{
    close(id);
}

void Server::Listen(int queueSize)
{
    if (listen(this->socket, queueSize) == -1)
    {
         perror("[Server]Error at listen().\n");
    }
}

void Server::Bind()
{
    if (bind(this->socket, (struct sockaddr *) &this->server, sizeof(struct sockaddr)) == -1)
    {
        perror("[Server]Error at bind().\n");
    }
}

void Server::WriteToAllClients(std::string message, int exclude)
{
    for (auto *client: clients)
    {
        if(client->GetSocket() == exclude)
        {
            continue;
        }

        write(client->GetSocket(), message.c_str(), message.size() + 1);
        //Write(client->GetSocket(), message);
    }
}

int Server::GetSocket()
{
    return this->socket;
}

Server::Server()
{
    bzero(&this->server, sizeof(this->server));
    FD_ZERO(&this->master);
}

void Server::Select(fd_set &masterCopy)
{
    masterCopy = this->master;
    select(this->nfds + 1, &masterCopy, nullptr, nullptr, nullptr);
}

Server::~Server()
= default;
