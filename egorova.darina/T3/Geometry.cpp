#include "Geometry.h"
#include <cmath>
#include <algorithm>

double getArea(const Polygon& p) {
    double area = 0.0; size_t n = p.points.size();
    for (size_t i = 0; i < n; ++i) {
        area += (static_cast<double>(p.points[i].x) * p.points[(i + 1) % n].y -
                 static_cast<double>(p.points[(i + 1) % n].x) * p.points[i].y);
    }
    return std::abs(area) / 2.0;
}

struct Segment { Point a, b; };

bool segmentsIntersect(Segment s1, Segment s2) {
    auto cp = [](Point a, Point b, Point c) {
        return static_cast<long long>(b.x - a.x) * (c.y - a.y) - static_cast<long long>(b.y - a.y) * (c.x - a.x);
    };
    auto on = [](Point p, Segment s) {
        return p.x <= std::max(s.a.x, s.b.x) && p.x >= std::min(s.a.x, s.b.x) &&
               p.y <= std::max(s.a.y, s.b.y) && p.y >= std::min(s.a.y, s.b.y);
    };
    long long d1 = cp(s2.a, s2.b, s1.a), d2 = cp(s2.a, s2.b, s1.b);
    long long d3 = cp(s1.a, s1.b, s2.a), d4 = cp(s1.a, s1.b, s2.b);
    if (((d1 > 0 && d2 < 0) || (d1 < 0 && d2 > 0)) && ((d3 > 0 && d4 < 0) || (d3 < 0 && d4 > 0))) return true;
    if (d1 == 0 && on(s1.a, s2)) return true;
    if (d2 == 0 && on(s1.b, s2)) return true;
    if (d3 == 0 && on(s2.a, s1)) return true;
    if (d4 == 0 && on(s2.b, s1)) return true;
    return false;
}

bool isInside(Point pt, const Polygon& poly) {
    bool res = false;
    for (size_t i = 0, j = poly.points.size() - 1; i < poly.points.size(); j = i++) {
        if (((poly.points[i].y > pt.y) != (poly.points[j].y > pt.y)) &&
            (pt.x < (poly.points[j].x - poly.points[i].x) * (pt.y - poly.points[i].y) /
            static_cast<double>(poly.points[j].y - poly.points[i].y) + poly.points[i].x))
            res = !res;
    }
    return res;
}

bool polygonsIntersect(const Polygon& p1, const Polygon& p2) {
    for (size_t i = 0; i < p1.points.size(); ++i) {
        Segment s1 = {p1.points[i], p1.points[(i + 1) % p1.points.size()]};
        for (size_t j = 0; j < p2.points.size(); ++j) {
            Segment s2 = {p2.points[j], p2.points[(j + 1) % p2.points.size()]};
            if (segmentsIntersect(s1, s2)) return true;
        }
    }
    return (!p1.points.empty() && isInside(p1.points[0], p2)) ||
           (!p2.points.empty() && isInside(p2.points[0], p1));
}
