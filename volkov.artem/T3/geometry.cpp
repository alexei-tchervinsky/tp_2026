#include "geometry.hpp"

#include <sstream>
#include <cmath>

std::istream &operator>>(std::istream &in, Point &point) {
    char leftBracket = 0;
    char semicolon = 0;
    char rightBracket = 0;

    in >> leftBracket;
    if (leftBracket != '(') {
        in.setstate(std::ios::failbit);
        return in;
    }

    in >> point.x;
    in >> semicolon;
    if (semicolon != ';') {
        in.setstate(std::ios::failbit);
        return in;
    }

    in >> point.y;
    in >> rightBracket;
    if (rightBracket != ')') {
        in.setstate(std::ios::failbit);
        return in;
    }

    return in;
}

std::istream &operator>>(std::istream &in, Polygon &polygon) {
    size_t count = 0;
    in >> count;

    if (!in || count < 3) {
        in.setstate(std::ios::failbit);
        return in;
    }

    std::vector<Point> points(count);

    for (size_t i = 0; i < count; ++i) {
        in >> points[i];
        if (!in) {
            return in;
        }
    }

    polygon.points = points;
    return in;
}

bool operator==(const Point &left, const Point &right) {
    return left.x == right.x && left.y == right.y;
}

bool operator==(const Polygon &left, const Polygon &right) {
    return left.points == right.points;
}

bool isOnlySpaces(std::istream &in) {
    char symbol = 0;

    while (in >> symbol) {
        return false;
    }

    return true;
}

bool readPolygonFromLine(const std::string &line, Polygon &polygon) {
    std::istringstream in(line);
    in >> polygon;

    if (!in) {
        return false;
    }

    return isOnlySpaces(in);
}

double getArea(const Polygon &polygon) {
    long long sum = 0;
    size_t size = polygon.points.size();

    for (size_t i = 0; i < size; ++i) {
        const Point &first = polygon.points[i];
        const Point &second = polygon.points[(i + 1) % size];

        sum += static_cast<long long>(first.x) * second.y;
        sum -= static_cast<long long>(second.x) * first.y;
    }

    return std::abs(sum) / 2.0;
}

bool isEvenVertexes(const Polygon &polygon) {
    return polygon.points.size() % 2 == 0;
}

bool isOddVertexes(const Polygon &polygon) {
    return polygon.points.size() % 2 != 0;
}

bool hasVertexCount(const Polygon &polygon, size_t count) {
    return polygon.points.size() == count;
}
