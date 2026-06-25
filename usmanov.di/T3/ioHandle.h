#ifndef IO_HANDLE_H
#define IO_HANDLE_H
#include "Polygon.h"
#include <iostream>

struct DelimiterIO {
    char expected;
};

std::istream& operator>>(std::istream& in, DelimiterIO&& dest);
std::istream& operator>>(std::istream& in, Point& dest);
std::istream& operator>>(std::istream& in, Polygon& dest);

#endif
