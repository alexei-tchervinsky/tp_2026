#ifndef POINT_HPP
#define POINT_HPP

#include <iostream>

struct Point
{
    int x, y;

    bool operator==(const Point& other) const
    {
        return x == other.x && y == other.y;
    }

    bool operator<(const Point& other) const
    {
        return (x < other.x) || (x == other.x && y < other.y);
    }
};

inline std::istream& operator>>(std::istream& in, Point& p)
{
    char lp = 0, semi = 0, rp = 0;
    int x = 0, y = 0;
    if (!(in >> lp) || lp != '(') { in.setstate(std::ios::failbit); return in; }
    if (!(in >> x)) { in.setstate(std::ios::failbit); return in; }
    if (!(in >> semi) || semi != ';') { in.setstate(std::ios::failbit); return in; }
    if (!(in >> y)) { in.setstate(std::ios::failbit); return in; }
    if (!(in >> rp) || rp != ')') { in.setstate(std::ios::failbit); return in; }
    p.x = x;
    p.y = y;
    return in;
}

inline std::ostream& operator<<(std::ostream& out, const Point& p)
{
    out << '(' << p.x << ';' << p.y << ')';
    return out;
}

#endif
