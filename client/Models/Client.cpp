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
{
    this->m_socket = socket;
}

int Client::getSocket() const
{
    return this->m_socket;
}
