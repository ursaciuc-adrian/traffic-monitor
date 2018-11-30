#include <utility>

#pragma once

#include <string>
#include <unordered_map>

enum ResponseType
{
    Success,
    Error,
    Quit,
    None
};


static std::unordered_map<ResponseType, std::string> ResponseTypeMap =
{
    { Success, "Success" },
    { Error, "Error" },
    { Quit, "Quit" },
    { None, "None" }
};

class Response
{
    std::string value;
    ResponseType type;

public:
    Response()
    {
        this->value = "";
        this->type = ResponseType(None);
    }

    Response(std::string value, ResponseType type)
    {
        this->value = value;
        this->type = type;
    }

    Response(std::string value, std::string type)
    {
        this->value = std::move(value);

        for(const auto& r: ResponseTypeMap)
        {
            if(r.second == type)
            {
                this->type = r.first;
            }
        }
    }

    std::string GetValue()
    {
        return value;
    }

    ResponseType GetType()
    {
        return type;
    }
};