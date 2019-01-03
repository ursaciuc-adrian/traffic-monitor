#include <utility>

#include <utility>

#include <utility>

#include "Client.h"
#include "../../Shared/Models/Street.h"

Client::Client(int socket)
    : m_socket(socket)
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

void Client::setLocation(Street *location)
{
    this->m_location = location;
}

Street* Client::getLocation() {
    return this->m_location;
}

int Client::getSpeed() {
   return this->m_speed;
}
