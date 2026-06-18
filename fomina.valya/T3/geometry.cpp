#include "geometry.hpp"
#include <numeric>
#include <cmath>
#include <algorithm>
#include <functional>

double getArea(const Polygon &poly)
{
    if (poly.points.size() < 3)
        return 0.0;
    double area = 0.0;
    size_t n = poly.points.size();

    area = std::accumulate(poly.points.begin(), poly.points.end(), 0.0,
                           [&poly, n](double sum, const Point &p)
                           {
                               size_t idx = &p - poly.points.data();
                               size_t next_idx = (idx + 1) % n;
                               return sum + (poly.points[idx].x * poly.points[next_idx].y) -
                               (poly.points[next_idx].x * poly.points[idx].y);
                           });

    return std::abs(area) / 2.0;
}

std::pair<Point, Point> getBounds(const Polygon &poly)
{
    if (poly.points.empty())
        return {{0, 0}, {0, 0}};

    auto result = std::accumulate(
        std::next(poly.points.begin()),
                                  poly.points.end(),
                                  std::make_pair(poly.points.front(), poly.points.front()),
                                  [](std::pair<Point, Point> acc, const Point &p)
                                  {
                                      acc.first.x = std::min(acc.first.x, p.x);
                                      acc.first.y = std::min(acc.first.y, p.y);
                                      acc.second.x = std::max(acc.second.x, p.x);
                                      acc.second.y = std::max(acc.second.y, p.y);
                                      return acc;
                                  });

    return result;
}

bool inBounds(const Polygon &poly, const std::pair<Point, Point> &bounds)
{
    auto self_bounds = getBounds(poly);
    return (self_bounds.first.x >= bounds.first.x) &&
    (self_bounds.first.y >= bounds.first.y) &&
    (self_bounds.second.x <= bounds.second.x) &&
    (self_bounds.second.y <= bounds.second.y);
}
