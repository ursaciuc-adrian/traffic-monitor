#include <sys/types.h>
#include <stdlib.h>
#include <iostream>
#include "../Shared/CommunicationHelper.h"
#include "Models/Server.cpp"
#include "Models/Response.h"
#include "Models/Command.h"
#include "Helpers/Deserializer.h"
#include "Handlers/Handler.h"
#include "Handlers/SpeedHandler.h"
#include "Handlers/AccidentHandler.h"
#include "Handlers/SubscribeHandler.h"
#include "Helpers/JsonHelper.h"
#include "Handlers/NotifierHandler.h"
#include "Handlers/LicensePlateHandler.h"

#define PORT 2026

std::vector<Handler*> handlers;

Response HandleCommand(const std::string &str, Client *client)
{
    const Command *command = deserializeInput(str);

    for(auto *handler: handlers)
    {
        if(handler->canHandle(command))
        {
            handler->handle(client);

            if(handler->hasResponse())
            {
                return handler->getResponse();
            }

            break;
        }
        else
        {
            if(handler->hasResponse())
            {
                return handler->getResponse();
            }
        }
    }

    return Response("Command not found.", Error);
}

int main()
{
    auto *server = new Server();

    handlers.push_back(new SpeedHandler(server));
    handlers.push_back(new AccidentHandler(server));
    handlers.push_back(new SubscribeHandler(server));
    handlers.push_back(new NotifierHandler(server));
    handlers.push_back(new LicensePlateHandler(server));

    server->createServer(PORT, 5);

    while (true)
    {
        fd_set copy;
        server->select(copy);

        if (FD_ISSET(server->getSocket(), &copy))
        {
            server->addClient();
        }

        if (FD_ISSET(0, &copy))
        {
            std::string message;
            Read(0, message);
            auto response = HandleCommand(message, nullptr);
            std::cout << response.getValue() << std::endl;
        }

        for (auto *client: server->getClients())
        {
            if (FD_ISSET(client->getSocket(), &copy))
            {
                std::string message;

                if(Read(client->getSocket(), message) == 0)
                {
                    server->removeClient(client);
                }
                else
                {
                    auto response = HandleCommand(message, client);

                    server->writeToClient(client, response.getValue());
                }
            }
        }
    }
}
