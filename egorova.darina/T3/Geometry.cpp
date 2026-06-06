#include "Geometry.h"
#include <cmath>
#include <algorithm>
#include <numeric>
#include <iterator>

// 1. Расчёт площади через std::inner_product (формула Гаусса)
double getArea(const Polygon& p) {
    if (p.points.size() < 3) return 0.0;

    double area = std::inner_product(
        p.points.begin(), std::prev(p.points.end()),
        std::next(p.points.begin()),
        0.0,
        std::plus<double>(),
        [](const Point& a, const Point& b) {
            return static_cast<double>(a.x) * b.y - static_cast<double>(b.x) * a.y;
        }
    );

    area += static_cast<double>(p.points.back().x) * p.points.front().y -
            static_cast<double>(p.points.front().x) * p.points.back().y;

    return std::abs(area) / 2.0;
}

struct Segment { Point a, b; };

bool segmentsIntersect(Segment s1, Segment s2) {
    auto cp = [](Point a, Point b, Point c) {
        return static_cast<long long>(b.x - a.x) * (c.y - a.y) -
               static_cast<long long>(b.y - a.y) * (c.x - a.x);
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

// 2. Проверка точки внутри полигона через std::inner_product (Ray Casting)
bool isInside(Point pt, const Polygon& poly) {
    const auto& pts = poly.points;
    if (pts.size() < 3) return false;

    bool res = std::inner_product(
        pts.begin(), std::prev(pts.end()),
        std::next(pts.begin()),
        false,
        std::bit_xor<bool>(),
        [&pt](const Point& pi, const Point& pj) {
            return ((pi.y > pt.y) != (pj.y > pt.y)) &&
                   (pt.x < (pj.x - pi.x) * (pt.y - pi.y) / static_cast<double>(pj.y - pi.y) + pi.x);
        }
    );

    if (((pts.back().y > pt.y) != (pts.front().y > pt.y)) &&
        (pt.x < (pts.front().x - pts.back().x) * (pt.y - pts.back().y) /
        static_cast<double>(pts.front().y - pts.back().y) + pts.back().x)) {
        res = !res;
    }

    return res;
}

// 3. Проверка пересечения полигонов через std::any_of
bool polygonsIntersect(const Polygon& p1, const Polygon& p2) {
    if (p1.points.size() < 3 || p2.points.size() < 3) return false;

    bool borderIntersect = std::any_of(p1.points.begin(), p1.points.end(), [&](const Point& p1a) {
        const Point& p1b = (&p1a == &p1.points.back()) ? p1.points.front() : *(&p1a + 1);
        Segment s1 = {p1a, p1b};

        return std::any_of(p2.points.begin(), p2.points.end(), [&](const Point& p2a) {
            const Point& p2b = (&p2a == &p2.points.back()) ? p2.points.front() : *(&p2a + 1);
            Segment s2 = {p2a, p2b};
            return segmentsIntersect(s1, s2);
        });
    });

    if (borderIntersect) return true;

    return isInside(p1.points.front(), p2) || isInside(p2.points.front(), p1);
}
