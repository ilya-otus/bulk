#pragma once
#include <fstream>
class string;

class OutputHelper
{
public:
    ~OutputHelper();
    void endl();
    void operator<<(const std::string &o);
private:
    void delayedInit();
    static std::string genFileName();

private:
    std::fstream dumpFile;
    bool logIsOpened = false;
};
