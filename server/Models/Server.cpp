#pragma once

#include <strings.h>
#include <CommunicationHelper.h>
#include "Server.h"

Server::Server(int socket, int port, int queueSize)
{
    bzero(&this->server, sizeof(this->server));
    this->socket = socket;

    this->server.sin_family = AF_INET;
    this->server.sin_addr.s_addr = htonl(INADDR_ANY);
    this->server.sin_port = htons(static_cast<uint16_t>(port));

    //bind
    this->Bind();

    //listen
    this->Listen(queueSize);
}

int Server::AddClient()
{
    struct sockaddr_in from{};
    socklen_t length;

    bzero(&from, sizeof(from));
    length = sizeof(from);

    int id = accept(this->socket, (struct sockaddr *) &from, &length);

    auto *client = new Client(id, from, length);
    this->clients.push_back(client);

    return id;
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

void Server::WriteToAllClients(std::string message)
{
    for (auto *client: clients)
    {
        Write(client->GetId(), message);
    }
}

Server::~Server()
= default;
