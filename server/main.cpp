#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
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
            write(client, welcomeMsg.c_str(), welcomeMsg.size() + 1);

            server->WriteToAllClients("new fish boys..\r\n", client);
        }

        for (auto *client: server->clients)
        {
            if (FD_ISSET(client->GetSocket(), &copy))
            {
                char buf[500];
                bzero(buf, 500);

                read(client->GetSocket(), buf, 500);
                printf("Mesaj de la %d: %s\n", client->GetSocket(), buf);
                server->WriteToAllClients(buf, client->GetSocket());
            }
        }
    }
}
