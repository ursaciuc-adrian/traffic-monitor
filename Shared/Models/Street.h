#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include "../Libs/json.hpp"

#define STREETS "../../Shared/streets.json"

using json = nlohmann::json;

class Street {
public:
    int id;
    int from;
    int to;
    std::string name;
    int speedLimit;

    Street() = default;
    ~Street() = default;

    static json fileToJson(const std::string &path)
    {
        std::ifstream i(path);

        json jsonFile = json::parse(i);
        i.close();

        return jsonFile;
    }

    static Street* getStreet(int id)
    {
        auto *street = new Street();
        json streets = fileToJson(STREETS);

        for(const auto &s: streets)
        {
            if(s["id"] == id)
            {
                street->id = id;
                street->from = s["from"];
                street->to = s["to"];
                street->name = s["name"];
                street->speedLimit = s["speedLimit"];

                return street;
            }
        }
        return street;
    }

    static std::vector<Street*> getStreets()
    {
        std::vector<Street*> streetsV;
        json streets = fileToJson(STREETS);

        for(const auto &s: streets)
        {
            auto *street = new Street();

            street->id = s["id"];
            street->from = s["from"];
            street->to = s["to"];
            street->name = s["name"];
            street->speedLimit = s["speedLimit"];

            streetsV.push_back(street);
        }
        return streetsV;
    }
};