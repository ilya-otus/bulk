#include "output_helper.h"
#include <iostream>
#include <ctime>
#include <string>

OutputHelper::~OutputHelper() {
    if (logIsOpened) {
        dumpFile.close();
    }
}

void OutputHelper::endl() {
    std::cout << std::endl;
    delayedInit();
    if (logIsOpened) {
        dumpFile << std::endl;
    }
}

void OutputHelper::operator<<(const std::string &o) {
    std::cout << o;
    delayedInit();
    if (logIsOpened) {
        dumpFile << o;
    }
}
void OutputHelper::delayedInit() {
    if (!logIsOpened) {
        dumpFile.open(genFileName(), std::fstream::out);
        logIsOpened = dumpFile.is_open();
    }
}
std::string OutputHelper::genFileName() {
    std::string fileName("bulk");
    fileName += std::to_string(std::time(nullptr));
    fileName += ".log";
    return fileName;
}
