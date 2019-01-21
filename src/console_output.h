#pragma once
#include "output_item_interface.h"

class ConsoleOutput : public IOutputItem
{
public:
    void endl() override;
    void operator<<(const std::string &o) override;
    bool isAvailable() const override;
};
