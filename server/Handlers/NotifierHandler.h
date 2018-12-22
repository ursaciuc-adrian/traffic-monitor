#pragma once

#include "../Models/Command.h"
#include "Handler.h"
#include "../Models/Client.h"

class NotifierHandler: public Handler
{
public:
    explicit NotifierHandler(Server *server);

    bool canHandle(const Command *command) override;
    void handle(Client *client) override;
};