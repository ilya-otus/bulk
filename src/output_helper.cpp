#include "output_helper.h"
#include <iostream>
#include <ctime>
#include <string>
#include "file_output.h"

OutputHelper::OutputHelper(const size_t poolSize) {
    expandPool(poolSize);
}

OutputHelper::~OutputHelper() {
    reducePool(0);
    for (size_t i = mPermanentOutputs.size(); i >= 0; --i) {
        delete mPermanentOutputs[i];
    }
}

void OutputHelper::setPoolSize(const size_t newSize) {
    if (newSize > mProcessingPool.size()) {
        expandPool(newSize);
    } else if (newSize < mProcessingPool.size()) {
        reducePool(newSize);
    }
}

void OutputHelper::addPermanentOutput(IOutputItem *outputItem) {
    mPermanentOutputs.push_back(outputItem);
}

void OutputHelper::expandPool(const size_t newSize) {
    mProcessingPool.resize(newSize);
    for (size_t i = mProcessingPool.size(); i < newSize; ++i) {
        mProcessingPool[i] = new FileOutput();
    }
}

void OutputHelper::reducePool(const size_t newSize) {
    for (size_t i = mProcessingPool.size(); i >= newSize; --i) {
        delete mProcessingPool[i];
    }
    mProcessingPool.resize(newSize);
}

void OutputHelper::endl() {
    ;
}

void OutputHelper::operator<<(const std::string &output) {
    for (auto permanentItem: mPermanentOutputs) {
        permanentItem << output;
    }
    while (true) {
        auto available = std::find_if(mProcessingPool.begin(), mProcessingPool.end(), [](IOutputItem *item) { return item.isAvailable(); });
        if (available != mProcessingPool.end()) {
            poolItem << output;
            break;
        }
    }
}

