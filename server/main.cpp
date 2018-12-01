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
            int client = server->AddClient();

            string welcomeMsg = "Welcome to the Awesome Chat Server!\r\n";
            // Write(client, welcomeMsg);
            write(client, welcomeMsg.c_str(), welcomeMsg.size() + 1);

            server->WriteToAllClients("new fish boys..\r\n", client);
        }

        for (auto *client: server->clients)
        {
            if (FD_ISSET(client->GetSocket(), &copy))
            {
                string buf;

               // Read(client->GetSocket(), buf);
                char buff[200];
                read(client->GetSocket(), buff, 200);
                string buff2(buff);
                printf("Mesaj de la %d: %s\n", client->GetSocket(), buff);
                server->WriteToAllClients(buff2, client->GetSocket());
            }
        }
    }
}
