#pragma once
#include <istream>
#include <memory>

class Handler;
class IBulk;
class BulkProxy
{
public:
    BulkProxy(size_t bulkSize);
    friend std::istream& operator>>(std::istream &is, BulkProxy &bulkProxy);
private:
    std::shared_ptr<IBulk> mBulk;
    std::shared_ptr<Handler> mCommandHandler;
    std::shared_ptr<Handler> mBraceHandler;
};
