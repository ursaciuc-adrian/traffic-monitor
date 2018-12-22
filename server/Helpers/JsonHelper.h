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
    static void AddClient(Client *client)
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
        std::cout << jsonFile.dump(4) << '\n';
         std::ofstream o(DATABASE);
         o << std::setw(4) << jsonFile << std::endl;
         o.close();
    }
};
