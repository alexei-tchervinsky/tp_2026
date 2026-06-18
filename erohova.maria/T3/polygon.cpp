#include "polygon.hpp"
#include <algorithm>
#include <numeric>
#include <cmath>

double getArea(const Polygon& polygon) {
    if (polygon.points.size() < 3) return 0.0;

    double area = 0.0;
    size_t n = polygon.points.size();

    std::vector<size_t> indices(n);
    std::iota(indices.begin(), indices.end(), 0);

    area = std::accumulate(indices.begin(), indices.end(), 0.0, [&](double sum, size_t i) {
        size_t next = (i + 1) % n;
        return sum + (polygon.points[i].x * polygon.points[next].y) - (polygon.points[next].x * polygon.points[i].y);
    });

    return std::abs(area) / 2.0;
}

int dotProduct(const Point& a, const Point& b, const Point& c) {
    int ba_x = a.x - b.x;
    int ba_y = a.y - b.y;
    int bc_x = c.x - b.x;
    int bc_y = c.y - b.y;
    return ba_x * bc_x + ba_y * bc_y;
}

bool hasRightAngle(const Polygon& polygon) {
    size_t n = polygon.points.size();
    if (n < 3) return false;

    std::vector<size_t> indices(n);
    std::iota(indices.begin(), indices.end(), 0);

    return std::any_of(indices.begin(), indices.end(), [&](size_t i) {
        size_t prev = (i == 0) ? n - 1 : i - 1;
        size_t next = (i + 1) % n;
        return dotProduct(polygon.points[prev], polygon.points[i], polygon.points[next]) == 0;
    });
}

bool comparePoints(const Point& a, const Point& b) {
    if (a.x != b.x) return a.x < b.x;
    return a.y < b.y;
}

bool isPermutation(Polygon p1, Polygon p2) {
    if (p1.points.size() != p2.points.size()) return false;

    std::sort(p1.points.begin(), p1.points.end(), comparePoints);
    std::sort(p2.points.begin(), p2.points.end(), comparePoints);

    return std::equal(p1.points.begin(), p1.points.end(), p2.points.begin());
}
