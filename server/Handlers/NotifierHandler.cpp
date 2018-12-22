#include <iostream>
#include <dirent.h>
#include <cstring>

#include "NotifierHandler.h"

NotifierHandler::NotifierHandler(Server *server)
        : Handler(server, false)
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

void NotifierHandler::handle(Client *client)
{
    m_server->writeToAllClients("notification.");
    m_response = Response("Notifications not implemented.", Success);
}



