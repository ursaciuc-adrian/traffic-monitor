#pragma once

#include "../Models/Command.h"
#include "../Models/Response.h"
#include "../Models/Client.h"

class Handler
{
protected:
    const Command *m_command{};
    Response m_response;
public:
    explicit Handler()
    {
        this->m_response = Response();
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
