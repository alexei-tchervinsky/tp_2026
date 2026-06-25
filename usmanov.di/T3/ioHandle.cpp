#include "ioHandle.h"

std::istream& operator>>(std::istream& in, DelimiterIO&& dest) {
    std::istream::sentry sentry(in);

    if (!sentry) {
        return in;
    }

    char c = '0';
    in >> c;

    if (in && (c != dest.expected)) {
        in.setstate(std::ios::failbit);
    }

    return in;
}

std::istream& operator>>(std::istream& in, Point& p) {
    std::istream::sentry sentry(in);

    if (!sentry) {
        return in;
    }

    int x = 0;
    int y = 0;

    in >> DelimiterIO{ '(' } >> x >> DelimiterIO{ ';' } >> y >> DelimiterIO{ ')' };

    if (in) {
        p.x_ = x;
        p.y_ = y;
    }

    return in;
}

std::istream& operator>>(std::istream& in, Polygon& p) {
    std::istream::sentry sentry(in);

    if (!sentry) {
        return in;
    }

    p.points_.clear();

    Point temp{ 0, 0 };
    int nPoints = 0;

    in >> nPoints;

    if (!in) {
        return in;
    }

    if (nPoints < 3) {
        in.setstate(std::ios_base::failbit);
        return in;
    }

    for (int i = 0; i < nPoints; ++i) {
        in >> temp;

        if (in) {
            p.points_.push_back(temp);
        }
        else {
            return in;
        }
    }

    return in;
}
