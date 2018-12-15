#include "bulk.h"

Bulk::Bulk(size_t bulkSize)
    : IBulk(),
    mBulkSize(bulkSize)
{
}

void Bulk::addCommand(const std::string &c) {
    if (data.size() == 0 || data.back().size() == mBulkSize) {
        newBulk();
    }
    data.back().emplace_back(c);
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
        data.erase(data.end() - 1);
    }
    for (auto bulk: data) {
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
    if (data.size() != 0) {
        dumpBulk(data.back());
    }
    data.emplace_back(BulkContainer());
}

