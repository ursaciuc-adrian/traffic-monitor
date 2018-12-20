#pragma once

#include <string>

class Argument {
private:
    std::string m_value;

public:
    Argument() = default;;
    explicit Argument(std::string arg);

    std::string getValue() const;

    ~Argument() = default;
};
