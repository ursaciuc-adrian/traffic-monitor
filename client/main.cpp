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
                    printf("Sending message to server: %d-- %s --", static_cast<int>(message.length()), message.c_str());
                    Write(client->getSocket(), message);
                }
                else
                {
                    printf("Received from server: -- %s --", message.c_str());
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
