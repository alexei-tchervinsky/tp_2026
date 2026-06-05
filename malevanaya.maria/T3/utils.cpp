#include "utils.hpp"
#include "iofmtguard.hpp"
#include <iostream>
#include <algorithm>
#include <numeric>
#include <iterator>
#include <array>
#include <limits>
#include <string>
#include <stdexcept>
#include <sstream>


bool parsePolygonArg(std::istream& in, Polygon& poly)
{
    std::size_t n = 0;
    if (!(in >> n) || n < 3) return false;

    std::vector<Point> pts;
    for (std::size_t i = 0; i < n; ++i) {
        Point p;
        if (!(in >> p)) return false;
        pts.push_back(p);
    }
    std::string extra;
    if (in >> extra) return false;

    poly.points = std::move(pts);
    return true;
}

void cmd::AREA(const std::vector<Polygon>& polygons, std::istream& is, std::ostream& os)
{
    std::string param;
    if (!(is >> param)) { os << "<INVALID COMMAND>\n"; return; }

    iofmtguard guard(os);
    os << std::fixed;
    os.precision(1);

    if (param == "EVEN")
    {
        os << std::accumulate(polygons.begin(), polygons.end(), 0.0,
            [](double acc, const Polygon& p)
            { return p.points.size() % 2 == 0 ? acc + polygonArea(p) : acc; }) << '\n';
    }
    else if (param == "ODD")
    {
        os << std::accumulate(polygons.begin(), polygons.end(), 0.0,
            [](double acc, const Polygon& p)
            { return p.points.size() % 2 != 0 ? acc + polygonArea(p) : acc; }) << '\n';
    }
    else if (param == "MEAN")
    {
        if (polygons.empty()) { os << "<INVALID COMMAND>\n"; return; }
        os << std::accumulate(polygons.begin(), polygons.end(), 0.0,
            [](double acc, const Polygon& p) { return acc + polygonArea(p); })
            / static_cast<double>(polygons.size()) << '\n';
    }
    else
    {
        try
        {
            const std::size_t nv = std::stoul(param);
            if (nv < 3) { os << "<INVALID COMMAND>\n"; return; }
            os << std::accumulate(polygons.begin(), polygons.end(), 0.0,
                [nv](double acc, const Polygon& p)
                { return p.points.size() == nv ? acc + polygonArea(p) : acc; }) << '\n';
        }
        catch (const std::exception&) { os << "<INVALID COMMAND>\n"; }
    }
}

void cmd::MAX(const std::vector<Polygon>& polygons, std::istream& is, std::ostream& os)
{
    std::string param;
    if (!(is >> param)) { os << "<INVALID COMMAND>\n"; return; }
    if (polygons.empty()) { os << "<INVALID COMMAND>\n"; return; }

    if (param == "AREA")
    {
        iofmtguard guard(os);
        os << std::fixed;
        os.precision(1);
        os << polygonArea(*std::max_element(polygons.begin(), polygons.end(),
            [](const Polygon& a, const Polygon& b)
            { return polygonArea(a) < polygonArea(b); })) << '\n';
    }
    else if (param == "VERTEXES")
    {
        os << std::max_element(polygons.begin(), polygons.end(),
            [](const Polygon& a, const Polygon& b)
            { return a.points.size() < b.points.size(); })->points.size() << '\n';
    }
    else { os << "<INVALID COMMAND>\n"; }
}

void cmd::MIN(const std::vector<Polygon>& polygons, std::istream& is, std::ostream& os)
{
    std::string param;
    if (!(is >> param)) { os << "<INVALID COMMAND>\n"; return; }
    if (polygons.empty()) { os << "<INVALID COMMAND>\n"; return; }

    if (param == "AREA")
    {
        iofmtguard guard(os);
        os << std::fixed;
        os.precision(1);
        os << polygonArea(*std::min_element(polygons.begin(), polygons.end(),
            [](const Polygon& a, const Polygon& b)
            { return polygonArea(a) < polygonArea(b); })) << '\n';
    }
    else if (param == "VERTEXES")
    {
        os << std::min_element(polygons.begin(), polygons.end(),
            [](const Polygon& a, const Polygon& b)
            { return a.points.size() < b.points.size(); })->points.size() << '\n';
    }
    else { os << "<INVALID COMMAND>\n"; }
}

void cmd::COUNT(const std::vector<Polygon>& polygons, std::istream& is, std::ostream& os)
{
    std::string param;
    if (!(is >> param)) { os << "<INVALID COMMAND>\n"; return; }

    if (param == "EVEN")
    {
        os << std::count_if(polygons.begin(), polygons.end(),
            [](const Polygon& p) { return p.points.size() % 2 == 0; }) << '\n';
    }
    else if (param == "ODD")
    {
        os << std::count_if(polygons.begin(), polygons.end(),
            [](const Polygon& p) { return p.points.size() % 2 != 0; }) << '\n';
    }
    else
    {
        try
        {
            const std::size_t nv = std::stoul(param);
            if (nv < 3) { os << "<INVALID COMMAND>\n"; return; }
            os << std::count_if(polygons.begin(), polygons.end(),
                [nv](const Polygon& p) { return p.points.size() == nv; }) << '\n';
        }
        catch (const std::exception&) { os << "<INVALID COMMAND>\n"; }
    }
}

void cmd::INFRAME(const std::vector<Polygon>& polygons, std::istream& is, std::ostream& os)
{
    std::string rest;
    std::getline(is, rest);
    std::istringstream iss(rest);
    Polygon poly;
    if (!parsePolygonArg(iss, poly)) { os << "<INVALID COMMAND>\n"; return; }

    if (polygons.empty()) { os << "<FALSE>\n"; return; }

    using BBox = std::array<int, 4>;
    const BBox bbox = std::accumulate(polygons.begin(), polygons.end(),
        BBox{ std::numeric_limits<int>::max(), std::numeric_limits<int>::min(),
              std::numeric_limits<int>::max(), std::numeric_limits<int>::min() },
        [](BBox acc, const Polygon& p) -> BBox {
            return std::accumulate(p.points.begin(), p.points.end(), acc,
                [](BBox a, const Point& pt) -> BBox {
                    return BBox{ std::min(a[0], pt.x), std::max(a[1], pt.x),
                                 std::min(a[2], pt.y), std::max(a[3], pt.y) };
                });
        });

    os << (std::all_of(poly.points.begin(), poly.points.end(),
        [&bbox](const Point& pt) {
            return pt.x >= bbox[0] && pt.x <= bbox[1] &&
                pt.y >= bbox[2] && pt.y <= bbox[3];
        }) ? "<TRUE>" : "<FALSE>") << '\n';
}

static bool hasRightAngle(const Polygon& poly)
{
    const auto& pts = poly.points;
    const std::size_t n = pts.size();
    std::vector<std::size_t> idx(n);
    std::iota(idx.begin(), idx.end(), std::size_t{ 0 });
    return std::any_of(idx.begin(), idx.end(),
        [&](std::size_t i) {
            const std::size_t prev = (i + n - 1) % n;
            const std::size_t next = (i + 1) % n;
            const int dx1 = pts[i].x - pts[prev].x, dy1 = pts[i].y - pts[prev].y;
            const int dx2 = pts[next].x - pts[i].x, dy2 = pts[next].y - pts[i].y;
            return (dx1 * dx2 + dy1 * dy2) == 0;
        });
}

void cmd::RIGHTSHAPES(const std::vector<Polygon>& polygons, std::istream&, std::ostream& os)
{
    os << std::count_if(polygons.begin(), polygons.end(), hasRightAngle) << '\n';
}
