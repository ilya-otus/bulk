#pragma once

class IBulk
{
public:
    virtual void addCommand(const std::string &c) = 0;
    virtual void startOfBlock() = 0;
    virtual void endOfBlock() = 0;
    virtual void dump() = 0;
};
