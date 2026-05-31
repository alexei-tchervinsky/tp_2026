#ifndef POLYGON_HPP
#define POLYGON_HPP

#include <iostream>
#include <string>
#include <vector>
#include "point.hpp"

struct Polygon
{
    std::vector<Point> points;

    bool operator==(const Polygon& other) const
    {
        return points == other.points;
    }
};

double polygonArea(const Polygon& poly);

bool parseLine(const std::string& line, Polygon& poly);

std::istream& operator>>(std::istream& in, Polygon& poly);
std::ostream& operator<<(std::ostream& out, const Polygon& poly);

#endif
