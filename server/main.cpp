#include <sys/types.h>
#include <stdlib.h>
#include <iostream>
#include "../Shared/CommunicationHelper.h"
#include "Models/Server.cpp"

#define PORT 2026

int main()
{
    auto *server = new Server();
    server->createServer(PORT, 5);

    while (true)
    {
        fd_set copy;
        server->select(copy);

        if (FD_ISSET(server->getSocket(), &copy))
        {
            server->addClient();
        }

        for (auto *client: server->getClients())
        {
            if (FD_ISSET(client->getSocket(), &copy))
            {
                std::string message;

                if(Read(client->getSocket(), message) == 0)
                {
                    server->removeClient(client);
                }
                else
                {
                    server->writeToAllClients(message, client->getSocket());
                }
            }
        }
    }
}
