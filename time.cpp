#include "time.h"

std::ostream& operator << (std::ostream& out, const Time& t) {
    if (t.h / 10 == 0) {
        out << "0";
    }
    out << t.h << ":";
    if (t.m / 10 == 0) {
        out << "0";
    }
    out << t.m;
    return out;
}
