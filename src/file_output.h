#pragma once
#include "output_item_interface.h"
#include <fstream>

class FileOutput final: public IOutputItem
{
public:
    ~FileOutput();
    void endl() override;
    void operator<<(const std::string &output) override;
    bool isAvailable() const override;
private:
    std::string genFileName() const;
    bool init();
private:
    bool mInitialized = false;
    std::fstream mDumpFile;
    inline static size_t suffixCounter = 0;
};
