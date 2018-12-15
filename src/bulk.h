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
    ~Bulk();
    virtual void addCommand(const std::string &cmd);
    virtual void startOfBlock();
    virtual void endOfBlock();
    virtual void dumpAll();
    virtual std::string fileName();

private:
    void dumpBulk(const BulkContainer &rawBulk);

private:
    std::vector<BulkContainer> mData;
    bool mBlockStarted = false;
    bool mBlockFinished = false;
    size_t mBulkSize;
    OutputHelper mOut;
};

