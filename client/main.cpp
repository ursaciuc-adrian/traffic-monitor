#include <iostream>
#include <strings.h>

#include "../Shared/CommunicationHelper.h"
#include "Models/Client.cpp"
#include "Models/Server.cpp"

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Sintaxa: %s <adresa_server> <port>\n", argv[0]);
        return -1;
    }

    auto *server = new Server(argv[1], std::stoi(argv[2]));

    auto *client = new Client(CreateSocket());
    client->ConnectToServer(server);

    std::string request;
    std::string response;

    switch (fork())
    {
        case -1:
            perror("fork");
            exit(1);

        case 0:
            while (true)
            {
                std::getline(std::cin, request);
               // Write(client->GetSocket(), request);
               write(client->GetSocket(), request.c_str(), 500);
            }

        default:
            while (true)
            {
                char buf[4096];
                bzero(buf, 4096);
                ssize_t bytesIn = read(client->GetSocket(), buf, 4096);
                printf("%s", buf);
            }
    }

    close(client->GetSocket());
}
