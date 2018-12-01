#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include "../Shared/CommunicationHelper.h"
#include "Models/Server.cpp"

using namespace std;

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
            server->WriteToAllClients("new fish boys..\r\n", client->GetSocket());
        }

        for (auto *client: server->clients)
        {
            if (FD_ISSET(client->GetSocket(), &copy))
            {
                string buf;

                Read(client->GetSocket(), buf);

                printf("Mesaj de la %d: %s\n", client->GetSocket(), buf.c_str());
                server->WriteToAllClients(buf, client->GetSocket());
            }
        }
    }
}
