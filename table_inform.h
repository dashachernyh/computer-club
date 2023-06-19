#pragma once
#include "time.h"

struct table_inform {
    std::string name;
    int table;
    Time start;
    Time count;
    bool empty;

    static int count_free;

    table_inform() : table(-1), start("00:00"), count("00:00"), empty(true) {}
};
int table_inform::count_free = 0;
