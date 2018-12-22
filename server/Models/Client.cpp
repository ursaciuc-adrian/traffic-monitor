#include <utility>

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

void Client::addSubscription(std::string subscription)
{
    this->m_subscriptions.push_back(subscription);
}

void Client::setLicensePlate(std::string licensePlate)
{
    this->m_licensePlate = std::move(licensePlate);
}

std::string Client::getLicensePlate()
{
    return this->m_licensePlate;
}

bool Client::hasSubscription(std::string subscription)
{
    for (const auto &sub: this->m_subscriptions)
    {
        if(sub == subscription)
        {
            return true;
        }
    }

    return false;
}

std::vector<std::string> Client::getSubscriptions()
{
    return this->m_subscriptions;
}
