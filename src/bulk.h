#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "bulk_interface.h"

class Bulk : public IBulk
{
public:
    Bulk(size_t bulkSize);
    virtual void addCommand(const std::string &c);
    virtual void startOfBlock();
    virtual void endOfBlock();
    virtual void dump();

private:
    std::vector<std::vector<std::string>> data;
    bool mBlockStarted = false;
    size_t mBulkSize;
};

