#include "polygon.hpp"
#include <sstream>
#include <iterator>
#include <numeric>
#include <cmath>
#include <algorithm>

static bool readPoints(std::istream& in, std::size_t n, std::vector<Point>& pts)
{
    pts.resize(n);
    std::generate_n(pts.begin(), n, [&]() -> Point
        {
            Point p{};
            in >> p;
            return p;
        });
    return !in.fail();
}

double polygonArea(const Polygon& poly)
{
    if (poly.points.size() < 3)
        return 0.0;

    const auto& pts = poly.points;
    const std::size_t n = pts.size();

    std::vector<std::size_t> idx(n);
    std::iota(idx.begin(), idx.end(), std::size_t{ 0 });

    const long long sum = std::accumulate(idx.begin(), idx.end(), 0LL,
        [&](long long acc, std::size_t i) -> long long
        {
            const std::size_t j = (i + 1) % n;
            return acc
                + static_cast<long long>(pts[i].x) * static_cast<long long>(pts[j].y)
                - static_cast<long long>(pts[j].x) * static_cast<long long>(pts[i].y);
        });

    return static_cast<double>(std::abs(sum)) / 2.0;
}

bool parseLine(const std::string& line, Polygon& poly)
{
    if (line.empty())
        return false;

    std::istringstream iss(line);
    std::size_t n = 0;
    if (!(iss >> n) || n < 3)
        return false;

    std::vector<Point> pts;
    if (!readPoints(iss, n, pts))
        return false;

    std::string extra;
    if (iss >> extra)
        return false;

    poly.points = std::move(pts);
    return true;
}

std::istream& operator>>(std::istream& in, Polygon& poly)
{
    std::string line;
    if (!std::getline(in, line))
        return in;

    std::istringstream iss(line);
    std::size_t n = 0;
    if (!(iss >> n) || n < 3)
    {
        in.setstate(std::ios::failbit);
        return in;
    }

    std::vector<Point> pts;
    if (!readPoints(iss, n, pts))
    {
        in.setstate(std::ios::failbit);
        return in;
    }

    std::string extra;
    if (iss >> extra)
    {
        in.setstate(std::ios::failbit);
        return in;
    }

    poly.points = std::move(pts);
    return in;
}

std::ostream& operator<<(std::ostream& out, const Polygon& poly)
{
    out << poly.points.size() << ' ';
    std::copy(poly.points.begin(), poly.points.end(),
        std::ostream_iterator<Point>(out, " "));
    return out;
}
