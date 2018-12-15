#include "bulk.h"

Bulk::Bulk(size_t bulkSize)
    : IBulk(),
    mBulkSize(bulkSize)
{
}

void Bulk::addCommand(const std::string &c) {
    if (mData.size() == 0 || mData.back().size() == mBulkSize) {
        newBulk();
    }
    mData.back().emplace_back(c);
}

void Bulk::startOfBlock() {
    mBlockStarted = true;
    newBulk();
}

void Bulk::endOfBlock() {
    mBlockStarted = false;
    newBulk();
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
    mOut << "bulk: ";
    for (auto item = rawBulk.begin(); item != rawBulk.end(); ++item) {
        mOut << *item;
        if (item != rawBulk.end()-1) {
            mOut << ", ";
        }
    }
    mOut.endl();
}

void Bulk::newBulk() {
    if (mData.size() != 0) {
        dumpBulk(mData.back());
    }
    mData.emplace_back(BulkContainer());
}

