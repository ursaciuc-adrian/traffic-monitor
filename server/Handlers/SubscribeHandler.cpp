#include <iostream>
#include <dirent.h>
#include <cstring>

#include "SubscribeHandler.h"
#include "../Helpers/JsonHelper.h"

SubscribeHandler::SubscribeHandler(Server *server)
        : Handler(server)
{
}

bool SubscribeHandler::canHandle(const Command *com)
{
    m_response = Response();

    if(com->value == "subscribe")
    {
        if(com->getArgument(0) != nullptr)
        {
            m_command = com;
            return true;
        }
        else
        {
            m_response = Response("No service provided.", Error);
        }
    }

    return false;
}

void SubscribeHandler::handle(Client *client)
{
    std::string subscription = this->m_command->getArgument(0)->getValue();
    if(client->hasSubscription(subscription))
    {
        m_response = Response("You are already subscribed to this service.", Success);
        return;
    }

    client->addSubscription(subscription);
    JsonHelper::updateClient(client);

    m_response = Response("Successfully subscribed to " + subscription + ".", Success);
}



