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

Client::Client(int socket)
    : m_socket(socket)
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
    ::select(this->m_socket + 1, &masterCopy, nullptr, nullptr, nullptr);
}

void Client::close()
{
    ::close(this->m_socket);
}
