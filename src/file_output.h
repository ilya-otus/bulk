#pragma once
#include <fstream>
#include "output_item_interface.h"

class FileOutput : public IOutputItem<FileOutput>
{
public:
    ~FileOutput();
    template<typename T>
    void output(const T &value) {
        if (init()) {
            for (const auto &v : value) {
                mDumpFile << v;
            }
            mInitialized = false;
            mDumpFile.close();
        }
    }

    bool isAvailable() const;
private:
    std::string genFileName() const;
    bool init();
private:
    bool mInitialized = false;
    std::fstream mDumpFile;
    inline static size_t suffixCounter = 0;
};
