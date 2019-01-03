#include <iostream>
#include <string>
#include <strings.h>
#include <cstring>

#include "../Shared/CommunicationHelper.h"
#include "Models/Client.cpp"
#include "Models/Server.cpp"
#include "../Shared/Models/Street.h"

void *UpdateSpeedAndLocation(void *ptr)
{
    while(true)
    {
        ((Client *) ptr)->updateLocation();
        ((Client *) ptr)->updateSpeed();
        sleep(60);
    }
}

int main(int argc, char *argv[])
{
    pthread_t thread;
    srand(time(nullptr));

    if (argc != 3)
    {
        Logger::LogError("Invalid arguments.");
        std::cout << "<server_ip> <port> <license_plate>(optional)" << std::endl;
        exit(EXIT_FAILURE);
    }

    auto *server = new Server(argv[1], std::stoi(argv[2]));

    std::string licensePlate;
    if(argv[3] != nullptr)
    {
        licensePlate.assign(argv[3]);
    }

    auto *client = new Client(CreateSocket(), licensePlate);
    client->connectToServer(server);
    client->updateLicensePlate();
    client->getStreets();

    if(pthread_create(&thread, nullptr, UpdateSpeedAndLocation, (void*) client))
    {
        exit(EXIT_FAILURE);
    }

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
                int code = Read(fd, message);
                if(code <= 0)
                {
                    Logger::LogError("Error occurred while reading.");
                    running = false;
                    break;
                }

                if (fd == 0)
                {
                    client->write(message);
                }
                else
                {
                    if(message != "quit")
                    {
                        Logger::LogMessage(message);
                    }
                }

                if(message == "quit")
                {
                    running = false;
                }
            }
        }
    }

    std::cout << "Closing the client. Bye!" << std::endl;
    client->close();

    return 0;
}
