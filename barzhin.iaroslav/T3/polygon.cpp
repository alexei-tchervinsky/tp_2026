#include <ostream>
#include <cmath>
#include <iomanip>
#include <numeric>

#include "polygon.hpp"
#include "iofmtguard.hpp"

const std::vector<Point> &Polygon::getPoints() const {
    return points;
}

void Polygon::addPoint(const Point p) {
    points.push_back(p);
}

double Polygon::getArea() const {
    if (points.size() < 3) {
        return 0.0;
    }

    double area = std::inner_product(
        points.begin(), points.end() - 1,
        points.begin() + 1,
        0.0,
        std::plus<double>(),
        [](const Point& p1, const Point& p2) {
            return (p1.x * p2.y) - (p2.x * p1.y);
        }
    );

    area += (points.back().x * points.front().y) - (points.front().x * points.back().y);

    return std::abs(area) / 2.0;
}

std::pair<Point, Point> Polygon::getBounds() const {
    if (points.empty()) {
        return {{0, 0}, {0, 0}};
    }

    return std::accumulate(
        std::next(points.begin()),
        points.end(),
        std::make_pair(points.front(), points.front()),
        [](std::pair<Point, Point> acc, const Point& p) {
            acc.first.x = std::min(acc.first.x, p.x);
            acc.first.y = std::min(acc.first.y, p.y);
            acc.second.x = std::max(acc.second.x, p.x);
            acc.second.y = std::max(acc.second.y, p.y);
            return acc;
        }
    );
}

bool Polygon::inBounds(std::pair<Point, Point> bounds) const {
    auto self_bounds = this->getBounds();
    return (self_bounds.first.x >= bounds.first.x) &&
           (self_bounds.first.y >= bounds.first.y) &&
           (self_bounds.second.x <= bounds.second.x) &&
           (self_bounds.second.y <= bounds.second.y);
}

bool Polygon::operator==(const Polygon &other) const {
    return points == other.points;
}

std::istream & operator>>(std::istream &is, DelimiterIO &&dest) {
    std::istream::sentry sentry(is);
    if (!sentry) return is;
    char c = '0';
    is >> c;
    if (is && (c != dest.exp)) is.setstate(std::ios::failbit);
    return is;
}

std::istream & operator>>(std::istream &is, IntIO &&dest) {
    std::istream::sentry sentry(is);
    if (!sentry) return is;
    return is >> dest.ref;
}

std::istream & operator>>(std::istream &is, Polygon &dest) {
    std::istream::sentry sentry(is);
    if (!sentry) return is;

    Polygon input;
    int expected_point_count = 0;

    is >> IntIO{expected_point_count};
    if (!is || expected_point_count < 3) {
        is.setstate(std::ios::failbit);
        return is;
    }

    for (std::size_t i = 0; i < static_cast<std::size_t>(expected_point_count); ++i) {
        Point point;

        if (!(is >> DelimiterIO{'('}
                  >> IntIO{point.x}
                  >> DelimiterIO{';'}
                  >> IntIO{point.y}
                  >> DelimiterIO{')'})) {
            return is;
        }

        input.addPoint(point);
    }
    dest = std::move(input);
    return is;
}

std::ostream & operator<<(std::ostream &os, const Polygon &obj) {
    std::ostream::sentry sentry(os);
    if (!sentry) return os;
    iofmtguard fmtguard(os);
    // format: n (x;y) (x;y) ... (x;y)
    auto vertices = obj.getPoints();
    os << vertices.size();
    for (const auto &vertex : vertices) {
        os << " (" << vertex.x << ";" << vertex.y << ")";
    }
    return os;
}
