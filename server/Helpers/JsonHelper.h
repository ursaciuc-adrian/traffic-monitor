#pragma once

#include <fstream>
#include <iostream>
#include <iomanip>
#include "../Models/Client.h"
#include "../Libs/json.hpp"

#define DATABASE "../clients.json"

using json = nlohmann::json;

class JsonHelper {
public:
    static void addClient(Client *client)
    {
        std::ifstream i(DATABASE);

        json jsonFile = json::parse(i);
        i.close();

        json clients = jsonFile["clients"];

        json clientJson = json::object();
        clientJson["licensePlate"] = client->getLicensePlate();
        clientJson["subscriptions"] = json::array();

        clients.push_back(clientJson);

        jsonFile["clients"] = clients;

        std::ofstream o(DATABASE);
        o << std::setw(4) << jsonFile << std::endl;
        o.close();
    }

    static bool getClient(std::string licensePlate, Client *client)
    {
        std::ifstream i(DATABASE);

        json jsonFile = json::parse(i);
        i.close();

        json clients = jsonFile["clients"];

        for(const auto &c: clients)
        {
            if(c["licensePlate"] == licensePlate)
            {
                for (const auto &subscription: c["subscriptions"])
                {
                    client->addSubscription(subscription);
                }
                return true;
            }
        }

        return false;
    }

    static bool clientExists(Client *client)
    {
        std::ifstream i(DATABASE);

        json jsonFile = json::parse(i);
        i.close();

        json clients = jsonFile["clients"];

        for(const auto &c: clients)
        {
            if(c["licensePlate"] == client->getLicensePlate())
            {
                return true;
            }
        }

        return false;
    }

    static void updateClient(Client *client)
    {
        std::ifstream i(DATABASE);

        json jsonFile = json::parse(i);
        i.close();

        if(!clientExists(client))
        {
            return;
        }

        json clients = jsonFile["clients"];

        for(auto &c: clients)
        {
            if(c["licensePlate"] == client->getLicensePlate())
            {
                json subscriptions = json::array();
                for(const auto &sub: client->getSubscriptions())
                {
                    subscriptions.push_back(sub);
                }

                c["subscriptions"] = subscriptions;
            }
        }

        jsonFile["clients"] = clients;

        std::ofstream o(DATABASE);
        o << std::setw(4) << jsonFile << std::endl;
        o.close();
    }
};
