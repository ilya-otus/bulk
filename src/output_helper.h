#pragma once
#include <fstream>
class string;

class OutputHelper
{
public:
    ~OutputHelper();
    void endl();
    void operator<<(const std::string &o);
    std::string fileName();

private:
    void delayedInit();
    static std::string genFileName();

private:
    std::fstream mDumpFile;
    bool mLogIsOpened = false;
    std::string mFileName;
};
