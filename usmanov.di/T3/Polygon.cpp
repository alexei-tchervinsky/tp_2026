#include "Polygon.h"
#include <cmath>
#include <vector>
#include <algorithm>
#include <numeric>
#include <iostream>

bool Point::operator==(const Point& other) const {
    return (other.x_ == x_) && (other.y_ == y_);
}

double area(const Polygon& polygon) {
    if (polygon.points_.size() < 3) {
        return 0.0;
    }

    std::vector<size_t> indices(polygon.points_.size());
    std::iota(indices.begin(), indices.end(), 0);

    double area = std::accumulate(indices.begin(), indices.end(), 0.0,
        [&](double acc, size_t i) {
            const Point& p1 = polygon.points_[i];
            const Point& p2 = polygon.points_[(i + 1) % polygon.points_.size()];

            return acc + (p1.x_ * p2.y_) - (p1.y_ * p2.x_);
        }
    );

    return std::abs(area) / 2.0;
}
