#pragma once
#include <string>
#include <ostream>

struct Time {
    int h, m;

    Time(int h = 0, int m = 0) : h(h), m(m) {}
    Time(std::string formal_time) {
        h = (formal_time[0] - '0') * 10 + (formal_time[1] - '0');
        m = (formal_time[3] - '0') * 10 + (formal_time[4] - '0');
    }

    Time operator + (const Time& t) {
        int h_new = h + t.h;
        int m_new = m + t.m;
        if (m_new >= 60) {
            h_new += m_new / 60;
            m_new = m_new - (m_new / 60) * 60;
        }
        return Time(h_new, m_new);
    }

    Time& operator += (const Time& t) {
        h += t.h;
        m += t.m;
        if (m >= 60) {
            h += m / 60;
            m = m - (m / 60) * 60;
        }
        return *this;
    }

    Time operator - (const Time& t) {
        int h_new = h - t.h;
        int m_new = m;
        if (m_new < t.m) {
            --h_new;
            m_new += 60;
        }
        m_new -=t.m;
        return Time(h_new, m_new);
    }

    bool operator < (const Time& t) {
        if (h < t.h || (h == t.h && m < t.m))
            return true;
        return false;
    }
    bool operator > (const Time& t) {
        if (h > t.h || (h == t.h && m > t.m))
            return true;
        return false;
    }

    void clear() {
        h = 0;
        m = 0;
    }
    int rounding() {
        int h_round = h;
        if (m > 0)
            return ++h_round;
        return h_round;
    }
};

std::ostream& operator << (std::ostream& out, const Time& t);
