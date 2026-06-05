#include "geometry.hpp"
#include <numeric>
#include <cmath>

namespace Geometry
{

    double get_area(const Polygon &polygon)
    {
        if (polygon.points.size() < 3)
        {
            return 0.0;
        }

        const auto &points = polygon.points;
        size_t n = points.size();
        size_t i = 0;

        long long area2 = std::accumulate(points.begin(), points.end(), 0LL,
                                          [&](long long sum, const Point &p1)
                                          {
                                              const Point &p2 = points[(i + 1) % n];
                                              long long step = static_cast<long long>(p1.x) * p2.y - static_cast<long long>(p2.x) * p1.y;
                                              i++;
                                              return sum + step;
                                          });

        return std::abs(area2) / 2.0;
    }
}
