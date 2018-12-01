#include <utility>

#include "Client.h"

Client::Client(int socket, std::string ip, int port)
{
    this->socket = socket;
    this->ip = std::move(ip);
    this->port = port;
}

Client::~Client()
= default;

int Client::GetSocket()
{
    return this->socket;
}