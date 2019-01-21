#include "bulk.h"

namespace Status {
const std::bitset<2> Started("01");
const std::bitset<2> Finished("10");
}

Bulk::Bulk(size_t bulkSize)
    : IBulk(),
    mBulkSize(bulkSize)
{
    mOut.setLoggingEnabled();
}

Bulk::~Bulk() {
    if (mData.back().size() != mBulkSize && mStatus == 0) {
        dumpBulk(mData.back());
    }
}

void Bulk::addCommand(const std::string &c) {
    if ((mData.size() == 0 || mData.back().size() == mBulkSize) && (mStatus & Status::Started) == 0) {
        mData.emplace_back(BulkContainer());
    }
    if ((mStatus & Status::Finished) != 0) {
        mData.emplace_back(BulkContainer());
        mStatus &= ~Status::Finished;
    }
    mData.back().emplace_back(c);
    if (mData.back().size() == mBulkSize && (mStatus & Status::Started) == 0) {
        dumpBulk(mData.back());
    }
}

void Bulk::startOfBlock() {
    mStatus = mStatus | Status::Started;
    if (mData.size() !=0 && mData.back().size() != mBulkSize) {
        dumpBulk(mData.back());
    }
    mData.emplace_back(BulkContainer());
}

void Bulk::endOfBlock() {
    mStatus &= (~Status::Started);
    mStatus |= Status::Finished;
    dumpBulk(mData.back());
}

void Bulk::dumpAll() {
    if ((mStatus & Status::Started) != 0) {
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

