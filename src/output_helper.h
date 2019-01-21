#pragma once
#include <fstream>
#include "output_item_interface.h"
#include <vector>

class string;

class OutputHelper
{
public:
    OutputHelper(size_t poolSize = 2, bool loggingEnabled = true);
    ~OutputHelper();
    void endl();
    void operator<<(const std::string &o);
    void setPoolSize(const size_t newSize);
    void setLoggingEnabled();
    void setLoggingDisabled();
private:
    void expandPool(const size_t newSize);
    void reducePool(const size_t newSize);
private:
    std::vector<IOutputItem *> mProcessingPool;
    bool mLoggingEnabled;
    IOutputItem *mLoggingItem;
};
