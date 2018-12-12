#include <iostream>
#include <string>
#include <strings.h>
#include <cstring>

#include "../Shared/CommunicationHelper.h"
#include "Models/Client.cpp"
#include "Models/Server.cpp"

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Sintax: %s <server_ip> <port>\n", argv[0]);
        return -1;
    }

    auto *server = new Server(argv[1], std::stoi(argv[2]));

    auto *client = new Client(CreateSocket());
    client->connectToServer(server);

    bool running = true;

    while(running)
    {
        fd_set copy;
        client->select(copy);

        for (int fd = 0; fd <= client->getSocket(); fd++)
        {
            if(FD_ISSET(fd, &copy))
            {
                std::string message;
                Read(fd, message);

                if (fd == 0)
                {
                    std::cout << "Sending message to server: " << message << std::endl;
                    Write(client->getSocket(), message);
                }
                else
                {
                    std::cout << "Received from server: " << message << std::endl;
                }

                if(message == "quit")
                {
                    printf("Closing the client. Bye!\n");
                    running = false;
                }
            }
        }
    }

    std::cout << "Closing the socket\n";
    client->close();

    return 0;
}
