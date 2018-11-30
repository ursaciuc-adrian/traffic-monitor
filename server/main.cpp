#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <signal.h>
#include <sys/wait.h>
#include <sys/resource.h>
#include <netinet/in.h>

#include "Models/Server.cpp"
#include "CommunicationHelper.h"

#define PORT 2027

int main()
{
    std::string msg;
    std::string msgrasp;

    auto *server = new Server(CreateSocket(), PORT, 5);

    printf("[Server]Waiting on port %d...\n", PORT);

    while (true)
    {
        int client = server->AddClient();

        switch (Fork())
        {
            case 0:
                if (client < 0)
                {
                    perror("[Server]Error at accept().\n");
                    continue;
                }

                printf("[Server]New client connected (ID: %d)\n", client);

                server->WriteToAllClients("[From server]A new client joined us.");

                while(true)
                {
                    std::string command;
                    Read(client, command);

                    if(command == "quit")
                    {
                        break;
                    }

                    server->WriteToAllClients(command);
                }

                server->CloseClient(client);
                exit(0);
            default:
                break;
        }
    }
}
