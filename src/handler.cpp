#include "handler.h"

Handler::Handler(std::shared_ptr<IBulk> b)
    : next(nullptr),
    bulk(b)
{ }

void Handler::setNext(std::shared_ptr<Handler> n) {
    next = n;
}

void Handler::add(std::shared_ptr<Handler> n) {
    if (next != nullptr) {
        next->add(n);
    } else {
        next = n;
    }
}

void Handler::handle(const std::string &cmd) {
    next->handle(cmd);
}

void Handler::startOfBlock() {
    if (bulk != nullptr) {
        bulk->startOfBlock();
    }
}

void Handler::endOfBlock() {
    if (bulk != nullptr) {
        bulk->endOfBlock();
    }
}

void Handler::addCommand(const std::string &cmd) {
    if (bulk != nullptr) {
        bulk->addCommand(cmd);
    }
}
