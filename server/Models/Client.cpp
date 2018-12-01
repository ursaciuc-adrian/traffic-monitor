#include "Client.h"

Client::Client(int socket, string ip, int port)
{
    this->socket = socket;
    this->ip = ip;
    this->port = port;
}

Client::~Client()
= default;

int Client::GetSocket()
{
    return this->socket;
}