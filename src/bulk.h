#pragma once
#include <algorithm>
#include <iostream>
#include <optional>
#include <string>
#include <tuple>
#include <vector>
#include <memory>

class IBulk
{
public:
    virtual void addCommand(const std::string &c) = 0;
    virtual void startOfBlock() = 0;
    virtual void endOfBlock() = 0;
    virtual void dump() = 0;
};

class Handler
{
public:
    Handler(std::shared_ptr<IBulk> b) : next(nullptr), bulk(b) {}
    void setNext(Handler *n) {
        next = n;
    }
    void add(Handler *n) {
        if (next != nullptr) {
            next->add(n);
        } else {
            next = n;
        }
    }
    virtual void handle(const std::string &cmd) {
        next->handle(cmd);
    }
protected:
    void startOfBlock() {
        if (bulk != nullptr) {
            bulk->startOfBlock();
        }
    }
    void endOfBlock() {
        if (bulk != nullptr) {
            bulk->endOfBlock();
        }
    }
    void addCommand(const std::string &cmd) {
        if (bulk != nullptr) {
            bulk->addCommand(cmd);
        }
    }
private:
    Handler *next;
    std::shared_ptr<IBulk> bulk;
};

class BraceHandler : public Handler
{
public:
    BraceHandler(std::shared_ptr<IBulk> bulk) : Handler(bulk) {}
    void handle(const std::string &cmd) final {
        if (cmd == "{") {
            if (openCount++ == 0) {
                startOfBlock();
            }
        } else if (cmd == "}") {
            if (--openCount == 0) {
                endOfBlock();
            }
        } else {
            Handler::handle(cmd);
        }
    }
private:
    int openCount = 0;
};

class CommandHandler : public Handler
{
public:
    CommandHandler(std::shared_ptr<IBulk> bulk) : Handler(bulk) {}
    void handle(const std::string &cmd) final {
        addCommand(cmd);
    }
};

class StreamWatcher
{
public:
    StreamWatcher(std::shared_ptr<IBulk> bulk) : mCommandHandler(bulk), mBraceHandler(bulk), mBulk(bulk) {
        mBraceHandler.setNext(&mCommandHandler);
    }
    friend std::istream& operator>>(std::istream &is, StreamWatcher &sw) {
        //for (std::string cmd; std::getline(is, cmd) && !cmd.empty(); ) {
        for (std::string cmd; std::getline(is, cmd); ) {
            sw.mBraceHandler.handle(cmd);
        }
        sw.mBulk->dump();
        return is;
    }
private:
    CommandHandler mCommandHandler;
    BraceHandler mBraceHandler;
    std::shared_ptr<IBulk> mBulk;
};

class Bulk : public IBulk
{
public:
    Bulk(size_t bulkSize) : IBulk(), mBulkSize(bulkSize) {}
    virtual void addCommand(const std::string &c) {
        if (data.size() == 0 || data.back().size() == mBulkSize) {
            data.emplace_back(std::vector<std::string>());
        }
        data.back().emplace_back(c);
    }

    virtual void startOfBlock() {
        mBlockStarted = true;
        data.emplace_back(std::vector<std::string>());
    }

    virtual void endOfBlock() {
        mBlockStarted = false;
        data.emplace_back(std::vector<std::string>());
    }

    virtual void dump() {
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

private:
    std::vector<std::vector<std::string>> data;
    bool mBlockStarted = false;
    size_t mBulkSize;
};

