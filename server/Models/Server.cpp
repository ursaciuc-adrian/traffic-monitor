
#include <strings.h>
#include "Server.h"

Server::Server(int port)
{
    bzero(&server, sizeof(server));

    this->server.sin_family = AF_INET;
    this->server.sin_addr.s_addr = htonl(INADDR_ANY);
    this->server.sin_port = htons(static_cast<uint16_t>(port));
}

int Server::AddClient(int socket)
{
    struct sockaddr_in from{};
    socklen_t length;

    bzero(&from, sizeof(from));
    length = sizeof(from);

    int client = accept(socket, (struct sockaddr *)&from, &length);

    this->clients.push_back(from);

    return client;
}

Server::~Server()
= default;
