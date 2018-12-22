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

public:
    explicit Handler(Server *server, bool forClient = true)
        :m_server(server)
    {
        this->m_response = Response();
        this->m_forClient = forClient;
    };

    ~Handler() = default;

    virtual bool canHandle(const Command *command) = 0;
    virtual void handle(Client *client) = 0;

    bool hasResponse()
    {
        return m_response.getType() != ResponseType(None);
    }

    Response getResponse()
    {
        return m_response;
    }
};
