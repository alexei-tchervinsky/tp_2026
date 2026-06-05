#ifndef GEOMETRY_HPP
#define GEOMETRY_HPP

#include <vector>
#include <string>
#include <iostream>
#include <cstddef>

struct Point {
    int x;
    int y;
};

struct Polygon {
    std::vector<Point> points;
};

std::istream &operator>>(std::istream &in, Point &point);

std::istream &operator>>(std::istream &in, Polygon &polygon);

bool operator==(const Point &left, const Point &right);

bool operator==(const Polygon &left, const Polygon &right);

bool isOnlySpaces(std::istream &in);

bool readPolygonFromLine(const std::string &line, Polygon &polygon);

double getArea(const Polygon &polygon);

bool isEvenVertexes(const Polygon &polygon);

bool isOddVertexes(const Polygon &polygon);

bool hasVertexCount(const Polygon &polygon, size_t count);

#endif
