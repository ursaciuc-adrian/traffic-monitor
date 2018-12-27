#include <utility>

#include <netinet/in.h>
#include <arpa/inet.h>
#include "Client.h"
#include "Server.h"
#include "../Helpers/Logger.h"

void Client::connectToServer(Server *server)
{
    if (connect(m_socket, (struct sockaddr *)&server->server, sizeof(struct sockaddr)) == -1)
    {
        Logger::LogError("Can't connect to the server.");
        exit(EXIT_FAILURE);
    }
}

Client::Client(int socket, std::string licensePlate)
    : m_socket(socket), m_licensePlate(std::move(licensePlate))
{
    FD_ZERO(&this->m_master);

    FD_SET(0, &this->m_master);
    FD_SET(this->m_socket, &this->m_master);
}

int Client::getSocket() const
{
    return this->m_socket;
}

void Client::select(fd_set &masterCopy)
{
    masterCopy = this->m_master;
    if(::select(this->m_socket + 1, &masterCopy, nullptr, nullptr, nullptr) == -1)
    {
        Logger::LogError("Error occurred at select.");
        exit(EXIT_FAILURE);
    }
}

void Client::close()
{
    ::close(this->m_socket);
}

void Client::updateSpeed(int speed)
{
    if(speed == -1)
    {
        int range = 20 - 100 + 1;
        m_speed = rand() % range + 20;
    }
    else
    {
        m_speed = speed;
    }

    this->write("update_speed " + std::to_string(this->m_speed));
}

void Client::write(std::string message)
{
    if(Write(this->getSocket(), message) <= 0)
    {
        Logger::LogError("Error occurred while writing to server.");
    }
}

std::string Client::generateLicensePlate()
{
    std::string licensePlate;

    licensePlate += 'A' + rand() % 26;
    licensePlate += 'A' + rand() % 26;
    licensePlate += std::to_string(rand() % 10);
    licensePlate += std::to_string(rand() % 10);
    licensePlate += 'A' + rand() % 26;
    licensePlate += 'A' + rand() % 26;
    licensePlate += 'A' + rand() % 26;

    return licensePlate;
}

void Client::updateLicensePlate()
{
    if(this->m_licensePlate.empty())
    {
        this->m_licensePlate = generateLicensePlate();
    }
    this->write("update_licensePlate " + this->m_licensePlate);
}

void Client::updateLocation()
{
    this->write("update_location " + std::to_string(1 + rand() % 3));
}
