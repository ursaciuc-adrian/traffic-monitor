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

    std::cout << "The server started on port " << port << std::endl;
}

void Server::AddClient()
{
    int socket = accept(this->socket, nullptr, nullptr);

    auto *client = new Client(socket, "127.0.0.1", 2026);
    this->clients.push_back(client);

    FD_SET(socket, &this->master);

    this->nfds = std::max(this->nfds, socket);

    std::cout << "#" << client->GetSocket() <<" | A new client connected to the server." << std::endl;

    std::string welcomeMessage = "#" + std::to_string(client->GetSocket()) + " | You are now connected to the server.";
    this->WriteToClient(client, welcomeMessage);
}

void Server::RemoveClient(Client *client)
{
    int index = -1;
    for (int i = 0; i < this->clients.size(); ++i)
    {
        if(this->clients[i]->GetSocket() == client->GetSocket())
        {
            index = i;
            break;
        }
    }

    if(index != -1)
    {
        this->clients.erase(this->clients.begin() + index);

        close(client->GetSocket());
        FD_CLR(client->GetSocket(), &this->master);

        std::cout << "#" << client->GetSocket() <<" | A client disconnected from the server." << std::endl;
    }
    else
    {
        // TODO: Handle error
    }
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
    for (auto *client: this->clients)
    {
        if(client->GetSocket() == exclude)
        {
            continue;
        }

        this->WriteToClient(client, message);
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

void Server::WriteToClient(Client *client, std::string message)
{
    Write(client->GetSocket(), std::move(message));
}

const std::vector<Client *> Server::GetClients()
{
    return this->clients;
}

Server::~Server()
= default;
