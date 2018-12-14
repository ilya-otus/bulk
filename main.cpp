#include "src/bulk.h"
#include <iostream>

int main(int, char **) {
    StreamWatcher sw(std::make_shared<Bulk>(5));
    std::cin >> sw;
    return 0;
}
