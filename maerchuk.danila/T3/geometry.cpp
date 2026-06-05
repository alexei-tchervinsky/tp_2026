#include "geometry.hpp"
#include <cmath>
#include <algorithm>
#include <numeric>

double getArea(const Polygon& polygon)
{
    if (polygon.points.size() < 3) return 0.0;

    const auto& pts = polygon.points;
    size_t num_pts = pts.size();

    double area = std::accumulate(
        pts.begin(), pts.end(), 0.0,
        [&pts, num_pts](double sum, const Point& p) {
            size_t idx = &p - &pts[0];
            size_t next_idx = (idx + 1) % num_pts;
            const Point& next_p = pts[next_idx];
            return sum + (p.x * next_p.y - next_p.x * p.y);
        }
    );
    return std::abs(area) / 2.0;
}

bool isRectangle(const Polygon& polygon)
{
    if (polygon.points.size() != 4) return false;

    const auto& p = polygon.points;

    auto v1x = p[1].x - p[0].x; auto v1y = p[1].y - p[0].y;
    auto v2x = p[2].x - p[1].x; auto v2y = p[2].y - p[1].y;
    auto v3x = p[3].x - p[2].x; auto v3y = p[3].y - p[2].y;
    auto v4x = p[0].x - p[3].x; auto v4y = p[0].y - p[3].y;

    auto dot1 = v1x * v2x + v1y * v2y;
    auto dot2 = v2x * v3x + v2y * v3y;
    auto dot3 = v3x * v4x + v3y * v4y;
    auto dot4 = v4x * v1x + v4y * v1y;

    return (dot1 == 0 && dot2 == 0 && dot3 == 0 && dot4 == 0);
}

bool onSegment(Point p, Point q, Point r) {
    return q.x <= std::max(p.x, r.x) && q.x >= std::min(p.x, r.x) &&
           q.y <= std::max(p.y, r.y) && q.y >= std::min(p.y, r.y);
}

int orientation(Point p, Point q, Point r) {
    int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
    if (val == 0) return 0;
    return (val > 0) ? 1 : 2;
}

bool doSegmentsIntersect(Point p1, Point q1, Point p2, Point q2) {
    int o1 = orientation(p1, q1, p2);
    int o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);

    if (o1 != o2 && o3 != o4) return true;
    if (o1 == 0 && onSegment(p1, p2, q1)) return true;
    if (o2 == 0 && onSegment(p1, q2, q1)) return true;
    if (o3 == 0 && onSegment(p2, p1, q2)) return true;
    if (o4 == 0 && onSegment(p2, q1, q2)) return true;
    return false;
}

bool isPointInPolygon(Point pt, const Polygon& poly) {
    if (poly.points.size() < 3) return false;
    bool inside = false;
    size_t n = poly.points.size();
    for (size_t i = 0, j = n - 1; i < n; j = i++) {
        bool cond1 = (poly.points[i].y > pt.y) != (poly.points[j].y > pt.y);
        if (cond1) {
            long long calc_x = (poly.points[j].x - poly.points[i].x);
            calc_x = calc_x * (pt.y - poly.points[i].y);
            calc_x = calc_x / (poly.points[j].y - poly.points[i].y);
            calc_x = calc_x + poly.points[i].x;
            if (pt.x < calc_x) {
                inside = !inside;
            }
        }
    }
    return inside;
}

bool doPolygonsIntersect(const Polygon& poly1, const Polygon& poly2)
{
    const auto& pts1 = poly1.points;
    const auto& pts2 = poly2.points;

    bool intersect = std::any_of(
        pts1.begin(), pts1.end(), [&pts1, &pts2](const Point& p1) {
            size_t i = &p1 - &pts1[0];
            Point q1 = pts1[(i + 1) % pts1.size()];

            return std::any_of(
                pts2.begin(), pts2.end(), [p1, q1, &pts2](const Point& p2) {
                    size_t j = &p2 - &pts2[0];
                    Point q2 = pts2[(j + 1) % pts2.size()];
                    return doSegmentsIntersect(p1, q1, p2, q2);
                }
            );
        }
    );
    if (intersect) return true;

    if (isPointInPolygon(pts1[0], poly2)) return true;
    if (isPointInPolygon(pts2[0], poly1)) return true;

    return false;
}
