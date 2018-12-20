#include <utility>

#include <netinet/in.h>
#include <arpa/inet.h>
#include "Client.h"
#include "Server.h"

void Client::connectToServer(Server *server)
{
    if (connect(m_socket, (struct sockaddr *)&server->server, sizeof(struct sockaddr)) == -1)
    {
        perror("[client]Eroare la connect().\n");
    }
}

Client::Client(int socket, std::string licensePlate)
    : m_socket(socket), m_licensePlate(std::move(licensePlate))
{
    FD_ZERO(&this->m_master);

    FD_SET(0, &this->m_master);
    FD_SET(this->m_socket, &this->m_master);

    this->updateSpeed();
}

int Client::getSocket() const
{
    return this->m_socket;
}

void Client::select(fd_set &masterCopy)
{
    masterCopy = this->m_master;
    ::select(this->m_socket + 1, &masterCopy, nullptr, nullptr, nullptr);
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

int Client::getSpeed() const
{
    return m_speed;
}

void Client::write(std::string message)
{
    Write(this->getSocket(), message);
}
