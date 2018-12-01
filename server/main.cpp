#include <sys/types.h>
#include <stdlib.h>
#include <iostream>
#include "../Shared/CommunicationHelper.h"
#include "Models/Server.cpp"

#define PORT 2026

int main()
{
    auto *server = new Server();
    server->CreateServer(PORT, 5);

    while (true)
    {
        fd_set copy;
        server->Select(copy);

        if (FD_ISSET(server->GetSocket(), &copy))
        {
            server->AddClient();
        }

        for (auto *client: server->GetClients())
        {
            if (FD_ISSET(client->GetSocket(), &copy))
            {
                std::string message;

                if(Read(client->GetSocket(), message) == 0)
                {
                    server->RemoveClient(client);
                }
                else
                {
                    server->WriteToAllClients(message, client->GetSocket());
                }
            }
        }
    }
}
