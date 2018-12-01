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
            auto* client = server->AddClient();

            string welcomeMsg = "Welcome to the Awesome Chat Server!\r\n";

            server->WriteToClient(client, welcomeMsg);
            server->WriteToAllClients("new fish boys..", client->GetSocket());
        }

        for (auto *client: server->clients)
        {
            if (FD_ISSET(client->GetSocket(), &copy))
            {
                std::string buf;

                if(Read(client->GetSocket(), buf) == 0)
                {
                    server->RemoveClient(client);
                }
                else
                {
                    server->WriteToAllClients(buf, client->GetSocket());
                }
            }
        }
    }
}
