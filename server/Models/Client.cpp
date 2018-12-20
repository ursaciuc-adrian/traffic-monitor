#include <utility>

#include <utility>

#include "Client.h"

Client::Client(int socket, std::string ip, int port)
    : m_socket(socket),
    m_ip(std::move(ip)),
    m_port(port)
{
}

Client::~Client()
= default;

int Client::getSocket()
{
    return this->m_socket;
}

void Client::setSpeed(int speed)
{
    this->m_speed = speed;
}
