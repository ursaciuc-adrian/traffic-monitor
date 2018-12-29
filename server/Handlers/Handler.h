#pragma once

#include "../Models/Command.h"
#include "../Models/Response.h"
#include "../Models/Client.h"
#include "../Models/Server.h"

class Handler
{
protected:
    const Command *m_command{};
    Response m_response;
    Server *m_server;
    bool m_forClient;
    bool m_forServer;

public:
    explicit Handler(Server *server, bool forClient = true, bool forServer = false)
        :m_server(server)
    {
        this->m_response = Response();
        this->m_forClient = forClient;
        this->m_forServer = forServer;
    };

    ~Handler() = default;

    virtual bool canHandle(const Command *command) = 0;
    virtual void handle(Client *client) = 0;
    virtual std::string getHelpText() = 0;

    virtual void handle(Client *client, bool isFromClient)
    {
        if((isFromClient && this->m_forClient) || (!isFromClient && this->m_forServer))
        {
            this->handle(client);
        }
        else
        {
            this->m_response = Response("You are not allowed to run this command.", Error);
        }
    }

    bool hasResponse()
    {
        return m_response.getType() != ResponseType(None);
    }

    Response getResponse()
    {
        return m_response;
    }
};
