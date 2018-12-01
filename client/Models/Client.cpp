#include <netinet/in.h>
#include <arpa/inet.h>
#include "Client.h"
#include "Server.h"

void Client::ConnectToServer(Server *server)
{
    /* ne conectam la server */
    if (connect(socket, (struct sockaddr *)&server->server, sizeof(struct sockaddr)) == -1)
    {
        perror("[client]Eroare la connect().\n");
    }
}

Client::Client(int socket)
{
    this->socket = socket;
}

int Client::GetSocket()
{
    return this->socket;
}
