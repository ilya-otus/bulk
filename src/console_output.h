#pragma once
#include <iostream>
#include <type_traits>
#include "output_item_interface.h"

class ConsoleOutput : public IOutputItem<ConsoleOutput>
{
public:
    template<typename T>
    void output(const T &value) {
        for (const auto &v : value) {
            std::cout << v;
        }
    }
    bool isAvailable() const;
};
