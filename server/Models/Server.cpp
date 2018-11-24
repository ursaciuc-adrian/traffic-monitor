
#include <strings.h>
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

    int client = accept(this->socket, (struct sockaddr *)&from, &length);

    this->clients.push_back(from);

    return client;
}

void Server::Listen(int queueSize)
{
    if (listen(this->socket, 5) == -1)
    {
        // perror("[server]Eroare la listen().\n");
    }
}

void Server::Bind()
{
/* atasam socketul */
    if (bind(this->socket, (struct sockaddr *) &this->server, sizeof(struct sockaddr)) == -1)
    {
//        perror("[server]Eroare la bind().\n");
//        return errno;
    }
}

Server::~Server()
= default;
