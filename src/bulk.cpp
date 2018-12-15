#include "bulk.h"

Bulk::Bulk(size_t bulkSize)
    : IBulk(),
    mBulkSize(bulkSize)
{}

void Bulk::addCommand(const std::string &c) {
    if (data.size() == 0 || data.back().size() == mBulkSize) {
        data.emplace_back(std::vector<std::string>());
    }
    data.back().emplace_back(c);
}

void Bulk::startOfBlock() {
    mBlockStarted = true;
    data.emplace_back(std::vector<std::string>());
}

void Bulk::endOfBlock() {
    mBlockStarted = false;
    data.emplace_back(std::vector<std::string>());
}

void Bulk::dump() {
    if (mBlockStarted) {
        data.erase(data.end() - 1);
    }
    for (auto bulk: data) {
        for (auto item : bulk) {
            std::cout << item << ", ";
        }
        std::cout << std::endl;
    }
}

