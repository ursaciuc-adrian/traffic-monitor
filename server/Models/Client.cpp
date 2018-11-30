#include "Client.h"

Client::Client(int id, struct sockaddr_in from, socklen_t length)
{
    this->id = id;
    this->from = from;
    this->length = length;
}

int Client::GetId()
{
    return this->id;
}

Client::~Client()
= default;
