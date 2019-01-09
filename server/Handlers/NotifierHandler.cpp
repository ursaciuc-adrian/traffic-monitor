#include <iostream>
#include <dirent.h>
#include <cstring>

#include "NotifierHandler.h"

NotifierHandler::NotifierHandler(Server *server)
        : Handler(server, false, true)
{
}

bool NotifierHandler::canHandle(const Command *com)
{
    m_response = Response();

    if(com->value == "notify")
    {
        if(com->getArgument(0) != nullptr)
        {
            if(com->getArgument(1) != nullptr)
            {
                m_command = com;
                return true;
            }
            else
            {
                m_response = Response("No message provided.", Error);
            }
        }
        else
        {
            m_response = Response("No service provided.", Error);
        }
    }

    return false;
}

void NotifierHandler::handle(Client *)
{
    for(auto client: this->m_server->getClients())
    {
        if(client->hasSubscription(this->m_command->getArgument(0)->getValue()))
        {
            this->m_server->writeToClient(client, this->m_command->getArgument(0)->getValue() + ": " + this->m_command->getArgument(1)->getValue());
        }
    }

    m_response = Response("Notification sent.", Success);
}

std::string NotifierHandler::getHelpText()
{
    return "notify <service> <message> - sends a message to all clients that are subscribed to a service";
}



