#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "bulk_interface.h"
#include "output_helper.h"

using BulkContainer = std::vector<std::string>;
class Bulk : public IBulk
{
public:
    Bulk(size_t bulkSize);
    virtual void addCommand(const std::string &c);
    virtual void startOfBlock();
    virtual void endOfBlock();
    virtual void dumpAll();

private:
    void dumpBulk(const BulkContainer &rawBulk);
    void newBulk();

private:
    std::vector<BulkContainer> data;
    bool mBlockStarted = false;
    size_t mBulkSize;
    OutputHelper mOut;
};

