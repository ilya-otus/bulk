#pragma once
#include <fstream>
#include "output_item_interface.h"

class string;

class OutputHelper
{
public:
    OutputHelper(const size_t poolSize = 1);
    ~OutputHelper();
    void endl();
    void operator<<(const std::string &o);
    void setPoolSize(const size_t newSize);
    void addPermanentOutput(IOutputItem *outputItem);
private:
    void expandPool(const size_t newSize);
    void reducePool(const size_t newSize);
private:
    std::vector<IOutputItem *> mProcessingPool;
    std::vector<IOutputItem *> mPermanentOutputs;
};
