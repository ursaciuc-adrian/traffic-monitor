#pragma once

#include <string>

class Client
{
private:
    std::string ip;
    int port;
public:
    Client(std::string ip, int port);
    int GetPort();
    std::string GetIp();

    ~Client();
};

Client::Client(std::string ip, int port)
{
    this->ip = std::move(ip);
    this->port = port;
}

int Client::GetPort()
{
    return this->port;
}

std::string Client::GetIp()
{
    return this->ip;
}

Client::~Client() = default;
