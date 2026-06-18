#include "geometry.hpp"
#include <numeric>
#include <cmath>
#include <algorithm>
#include <sstream>

double getArea(const Polygon& p) {
    if (p.points.size() < 3) return 0.0;
    double area = std::inner_product(
        p.points.begin(), p.points.end() - 1,
        p.points.begin() + 1,
        0.0,
        std::plus<double>(),
        [](const Point& a, const Point& b) {
            return static_cast<double>(a.x) * b.y - static_cast<double>(b.x) * a.y;
        }
    );
    area += static_cast<double>(p.points.back().x) * p.points.front().y - static_cast<double>(p.points.front().x) * p.points.back().y;
    return std::abs(area) / 2.0;
}

bool parsePolygon(const std::string& line, Polygon& p) {
    if (line.empty()) return false;
    std::istringstream iss(line);
    size_t size = 0;
    if (!(iss >> size) || size < 3) return false;

    std::vector<Point> temp;
    temp.reserve(size);

    for (size_t i = 0; i < size; ++i) {
        char space = '\0';
        if (!iss.get(space) || space != ' ') return false;

        char c1 = '\0', c2 = '\0', c3 = '\0';
        Point pt;
        if (!(iss >> c1 >> pt.x >> c2 >> pt.y >> c3)) return false;
        if (c1 != '(' || c2 != ';' || c3 != ')') return false;
        temp.push_back(pt);
    }

    char check = '\0';
    if (iss.get(check)) return false;

    p.points = std::move(temp);
    return true;
}
