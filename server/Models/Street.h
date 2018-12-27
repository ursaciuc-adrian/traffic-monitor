#pragma once

#include <string>

class Street {
public:
    int id;
    std::string name;
    int speedLimit;

    Street() = default;
    ~Street() = default;
};