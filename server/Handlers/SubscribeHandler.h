#pragma once

#include "../Models/Command.h"
#include "Handler.h"
#include "../Models/Client.h"

class SubscribeHandler: public Handler
{
public:
    explicit SubscribeHandler(Server *server);

    bool canHandle(const Command *command) override;
    void handle(Client *client) override;
};