#include <iostream>
#include <string>

#include "../Shared/CommunicationHelper.h"
#include "Models/Client.cpp"
#include "Models/Server.cpp"

using namespace std;

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
                Write(client->GetSocket(), request);
            }

        default:
            while (true)
            {
                Read(client->GetSocket(), response);
                cout << response;
            }
    }

    close(client->GetSocket());

    return 0;
}
