#include "console_output.h"
#include <iostream>

void ConsoleOutput::endl() {
    std::cout << std::endl;
}

void ConsoleOutput::operator<<(const std::string &output) {
    std::cout << output;
}

bool ConsoleOutput::isAvailable() const {
    return true;
}
