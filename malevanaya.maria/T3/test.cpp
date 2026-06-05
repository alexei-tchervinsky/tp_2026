#include <iostream>
#include <sstream>
#include <vector>
#include <cassert>
#include <cmath>
#include <numeric>
#include <algorithm>
#include "polygon.hpp"
#include "point.hpp"

void testPointIO()
{
    std::istringstream iss("(3;4)");
    Point p{};
    iss >> p;
    assert(p.x == 3 && p.y == 4);

    std::ostringstream oss;
    oss << p;
    assert(oss.str() == "(3;4)");

    std::istringstream iss2("(-1;-2)");
    Point q{};
    iss2 >> q;
    assert(q.x == -1 && q.y == -2);

    std::cout << "[pass] testPointIO\n";
}

void testPolygonIO()
{
    std::istringstream iss("3 (1;1) (1;3) (3;3)");
    Polygon poly;
    iss >> poly;
    assert(poly.points.size() == 3);
    assert(poly.points[0].x == 1 && poly.points[0].y == 1);
    assert(poly.points[2].x == 3 && poly.points[2].y == 3);
    std::cout << "[pass] testPolygonIO\n";
}

void testArea()
{
    Polygon tri;
    tri.points = { {0,0},{2,0},{0,2} };
    assert(std::abs(polygonArea(tri) - 2.0) < 1e-9);

    Polygon sq;
    sq.points = { {0,0},{1,0},{1,1},{0,1} };
    assert(std::abs(polygonArea(sq) - 1.0) < 1e-9);

    Polygon t2;
    t2.points = { {1,1},{1,3},{3,3} };
    assert(std::abs(polygonArea(t2) - 2.0) < 1e-9);

    Polygon t3;
    t3.points = { {0,0},{-2,0},{0,-2} };
    assert(std::abs(polygonArea(t3) - 2.0) < 1e-9);

    Polygon sq2;
    sq2.points = { {0,0},{0,1},{1,1},{1,0} };
    assert(std::abs(polygonArea(sq2) - 1.0) < 1e-9);

    std::cout << "[pass] testArea\n";
}

void testParseLine()
{
    Polygon p1;
    assert(!parseLine("2 (0;0) (1;1)", p1));
    assert(p1.points.empty());

    Polygon p2;
    assert(parseLine("3 (0;0) (1;0) (0;1)", p2));
    assert(p2.points.size() == 3);

    Polygon p3;
    assert(!parseLine("3 (0;0) (1;0) (0;1) extra", p3));

    Polygon p4;
    assert(!parseLine("", p4));

    std::cout << "[pass] testParseLine\n";
}

void testRightAngle()
{
    // helper
    auto hasRight = [](const Polygon& poly) -> bool
        {
            const auto& p = poly.points;
            const std::size_t m = p.size();
            std::vector<std::size_t> idx(m);
            std::iota(idx.begin(), idx.end(), std::size_t{ 0 });
            return std::any_of(idx.begin(), idx.end(),
                [&](std::size_t i)
                {
                    const std::size_t prev = (i + m - 1) % m;
                    const std::size_t next = (i + 1) % m;
                    const int dx1 = p[i].x - p[prev].x, dy1 = p[i].y - p[prev].y;
                    const int dx2 = p[next].x - p[i].x, dy2 = p[next].y - p[i].y;
                    return (dx1 * dx2 + dy1 * dy2) == 0;
                });
        };

    Polygon sq; sq.points = { {0,0},{1,0},{1,1},{0,1} };
    assert(hasRight(sq));

    Polygon rt; rt.points = { {0,0},{1,0},{0,1} };
    assert(hasRight(rt));

    Polygon tilt; tilt.points = { {0,2},{2,0},{0,-2},{-2,0} };
    assert(hasRight(tilt));

    Polygon tri; tri.points = { {0,0},{3,0},{1,2} };
    assert(!hasRight(tri));

    std::cout << "[pass] testRightAngle\n";
}

void testInframe()
{
    const int minX = 0, maxX = 6, minY = 0, maxY = 6;

    auto inFrame = [&](const Polygon& poly) -> bool
        {
            return std::all_of(poly.points.begin(), poly.points.end(),
                [minX, maxX, minY, maxY](const Point& pt)
                {
                    return pt.x >= minX && pt.x <= maxX &&
                        pt.y >= minY && pt.y <= maxY;
                });
        };

    Polygon inside; inside.points = { {0,0},{2,2},{2,0} };
    assert(inFrame(inside));

    Polygon outside; outside.points = { {-1,-1},{1,1},{1,0} };
    assert(!inFrame(outside));

    std::cout << "[pass] testInframe\n";
}

void testCommandOutputs()
{
    std::vector<Polygon> polys;
    {
        Polygon p; parseLine("3 (1;1) (1;3) (3;3)", p);
        polys.push_back(p);
        parseLine("4 (0;0) (0;1) (1;1) (1;0)", p = Polygon{});
        polys.push_back(p);
        parseLine("5 (0;0) (0;1) (1;2) (2;1) (2;0)", p = Polygon{});
        polys.push_back(p);
        parseLine("3 (0;0) (-2;0) (0;-2)", p = Polygon{});
        polys.push_back(p);
    }
    assert(polys.size() == 4);
    const auto cntOdd = std::count_if(polys.begin(), polys.end(),
        [](const Polygon& p) {
            return p.points.size() % 2 != 0;
        });
    const auto cntEven = std::count_if(polys.begin(), polys.end(),
        [](const Polygon& p) {
            return p.points.size() % 2 == 0;
        });
    assert(cntOdd == 3);
    assert(cntEven == 1);

    const auto cnt3 = std::count_if(polys.begin(), polys.end(),
        [](const Polygon& p) {
            return p.points.size() == 3;
        });
    assert(cnt3 == 2);

    const auto itMax = std::max_element(polys.begin(), polys.end(),
        [](const Polygon& a, const Polygon& b) {
            return a.points.size() < b.points.size();
        });
    assert(itMax->points.size() == 5);

    const auto itMin = std::min_element(polys.begin(), polys.end(),
        [](const Polygon& a, const Polygon& b) {
            return a.points.size() < b.points.size();
        });
    assert(itMin->points.size() == 3);

    std::cout << "[pass] testCommandOutputs\n";
}

void run_test()
{
    std::cout << "T3 tests\n";
    testPointIO();
    testPolygonIO();
    testArea();
    testParseLine();
    testRightAngle();
    testInframe();
    testCommandOutputs();
    std::cout << "end of tests\n";
}
