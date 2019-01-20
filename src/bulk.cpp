#include "bulk.h"

Bulk::Bulk(size_t bulkSize)
    : IBulk(),
    mBulkSize(bulkSize)
{
    mOut.setLoggingEnabled();
}

Bulk::~Bulk() {
    if (mData.back().size() != mBulkSize && !mBlockFinished && !mBlockStarted) {
        dumpBulk(mData.back());
    }
}

void Bulk::addCommand(const std::string &c) {
    if ((mData.size() == 0 || mData.back().size() == mBulkSize) && !mBlockStarted) {
        mData.emplace_back(BulkContainer());
    }
    if (mBlockFinished) {
        mData.emplace_back(BulkContainer());
        mBlockFinished = false;
    }
    mData.back().emplace_back(c);
    if (mData.back().size() == mBulkSize && !mBlockStarted) {
        dumpBulk(mData.back());
    }
}

void Bulk::startOfBlock() {
    mBlockStarted = true;
    if (mData.size() !=0 && mData.back().size() != mBulkSize) {
        dumpBulk(mData.back());
    }
    mData.emplace_back(BulkContainer());
}

void Bulk::endOfBlock() {
    mBlockStarted = false;
    mBlockFinished = true;
    dumpBulk(mData.back());
}

void Bulk::dumpAll() {
    if (mBlockStarted) {
        mData.erase(mData.end() - 1);
    }
    for (auto bulk: mData) {
        dumpBulk(bulk);
    }
}

void Bulk::dumpBulk(const BulkContainer &rawBulk) {
    std::string outputLine = "bulk: ";
    for (auto item = rawBulk.begin(); item != rawBulk.end(); ++item) {
        outputLine += *item;
        if (item != rawBulk.end()-1) {
            outputLine += ", ";
        }
    }
    mOut << outputLine;
}

