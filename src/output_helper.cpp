#include "output_helper.h"
#include <iostream>
#include <ctime>
#include <string>

OutputHelper::~OutputHelper() {
    if (mLogIsOpened) {
        mDumpFile.close();
    }
}

void OutputHelper::endl() {
    std::cout << std::endl;
    delayedInit();
    if (mLogIsOpened) {
        mDumpFile << std::endl;
    }
}

void OutputHelper::operator<<(const std::string &output) {
    std::cout << output;
    delayedInit();
    if (mLogIsOpened) {
        mDumpFile << output;
    }
}

void OutputHelper::delayedInit() {
    if (!mLogIsOpened) {
        mFileName = genFileName();
        mDumpFile.open(mFileName, std::fstream::out | std::fstream::trunc);
        mLogIsOpened = mDumpFile.is_open();
    }
}

std::string OutputHelper::genFileName() {
    std::string fileName("bulk");
    fileName += std::to_string(std::time(nullptr));
    fileName += ".log";
    return fileName;
}

std::string OutputHelper::fileName() {
    return mFileName;
}
