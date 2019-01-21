#pragma once
#include <string>

class IOutputItem
{
public:
    virtual ~IOutputItem() = default;
    virtual void endl() = 0;
    virtual void operator<<(const std::string &o) = 0;
    virtual bool isAvailable() const = 0;
};
