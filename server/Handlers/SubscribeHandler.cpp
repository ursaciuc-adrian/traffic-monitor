#include <iostream>
#include <dirent.h>
#include <cstring>

#include "SubscribeHandler.h"

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
    m_response = Response("Subscribe function not implemented.", Success);
}



