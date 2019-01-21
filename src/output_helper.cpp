#include "output_helper.h"
#include <iostream>
#include <string>
#include <algorithm>
#include "console_output.h"
#include "file_output.h"

OutputHelper::OutputHelper(size_t poolSize, bool loggingEnabled)
    : mLoggingEnabled(loggingEnabled) {
    expandPool(poolSize);
    mLoggingItem = nullptr;
    if (mLoggingEnabled) {
        mLoggingItem = new ConsoleOutput();
    }
}

OutputHelper::~OutputHelper() {
    reducePool(0);
    if (mLoggingEnabled) {
        delete mLoggingItem;
    }
}

void OutputHelper::setPoolSize(const size_t newSize) {
    if (newSize > mProcessingPool.size()) {
        expandPool(newSize);
    } else if (newSize < mProcessingPool.size()) {
        reducePool(newSize);
    }
}

void OutputHelper::expandPool(const size_t newSize) {
    size_t oldSize = mProcessingPool.size();
    mProcessingPool.resize(newSize);
    for (size_t i = oldSize; i < newSize; ++i) {
        mProcessingPool[i] = new FileOutput();
    }
}

void OutputHelper::reducePool(const size_t newSize) {
    size_t oldSize = mProcessingPool.size();
    for (size_t i = newSize; i < oldSize; ++i) {
        delete mProcessingPool[i];
    }
    mProcessingPool.resize(newSize);
}

void OutputHelper::operator<<(const std::string &output) {
    if (mLoggingEnabled) {
        (*mLoggingItem) << output;
        mLoggingItem->endl();
    }
    while (true) {
        auto available = std::find_if(mProcessingPool.begin(), mProcessingPool.end(), [](IOutputItem *item) { return item->isAvailable(); });
        if (available != mProcessingPool.end()) {
            (**available) << output;
            (*available)->endl();
            break;
        }
    }
}

void OutputHelper::setLoggingEnabled() {
}

void OutputHelper::setLoggingDisabled() {
}
