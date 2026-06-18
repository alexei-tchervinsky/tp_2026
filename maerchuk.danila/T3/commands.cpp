#include "commands.hpp"
#include "parsing.hpp"
#include <iostream>
#include <algorithm>
#include <numeric>
#include <iomanip>

void handleArea(const std::vector<Polygon>& polygons, std::istream& is)
{
    std::string arg;
    if (!(is >> arg)) { std::cout << "<INVALID COMMAND>\n"; return; }

    double total_area = 0.0;

    if (arg == "EVEN") {
        total_area = std::accumulate(polygons.begin(), polygons.end(), 0.0,
            [](double sum, const Polygon& p) {
                return sum + (p.points.size() % 2 == 0 ? getArea(p) : 0.0);
            });
    } else if (arg == "ODD") {
        total_area = std::accumulate(polygons.begin(), polygons.end(), 0.0,
            [](double sum, const Polygon& p) {
                return sum + (p.points.size() % 2 != 0 ? getArea(p) : 0.0);
            });
    } else if (arg == "MEAN") {
        if (polygons.empty()) { std::cout << "<INVALID COMMAND>\n"; return; }
        double sum_area = std::accumulate(polygons.begin(), polygons.end(), 0.0,
            [](double sum, const Polygon& p) { return sum + getArea(p); });
        total_area = sum_area / polygons.size();
    } else {
        try {
            long long num = std::stoll(arg);
            if (num < 3) { std::cout << "<INVALID COMMAND>\n"; return; }
            total_area = std::accumulate(polygons.begin(), polygons.end(), 0.0,
                [num](double sum, const Polygon& p) {
                    bool match = p.points.size() == static_cast<size_t>(num);
                    return sum + (match ? getArea(p) : 0.0);
                });
        } catch (...) {
            std::cout << "<INVALID COMMAND>\n";
            return;
        }
    }
    std::cout << std::fixed << std::setprecision(1) << total_area << "\n";
}

void handleMax(const std::vector<Polygon>& polygons, std::istream& is)
{
    std::string arg;
    if (!(is >> arg) || polygons.empty()) { std::cout << "<INVALID COMMAND>\n"; return; }

    if (arg == "AREA") {
        auto it = std::max_element(polygons.begin(), polygons.end(),
            [](const Polygon& a, const Polygon& b) { return getArea(a) < getArea(b); });
        std::cout << std::fixed << std::setprecision(1) << getArea(*it) << "\n";
    } else if (arg == "VERTEXES") {
        auto it = std::max_element(polygons.begin(), polygons.end(),
            [](const Polygon& a, const Polygon& b) {
                return a.points.size() < b.points.size();
            });
        std::cout << it->points.size() << "\n";
    } else {
        std::cout << "<INVALID COMMAND>\n";
    }
}

void handleMin(const std::vector<Polygon>& polygons, std::istream& is)
{
    std::string arg;
    if (!(is >> arg) || polygons.empty()) { std::cout << "<INVALID COMMAND>\n"; return; }

    if (arg == "AREA") {
        auto it = std::min_element(polygons.begin(), polygons.end(),
            [](const Polygon& a, const Polygon& b) { return getArea(a) < getArea(b); });
        std::cout << std::fixed << std::setprecision(1) << getArea(*it) << "\n";
    } else if (arg == "VERTEXES") {
        auto it = std::min_element(polygons.begin(), polygons.end(),
            [](const Polygon& a, const Polygon& b) {
                return a.points.size() < b.points.size();
            });
        std::cout << it->points.size() << "\n";
    } else {
        std::cout << "<INVALID COMMAND>\n";
    }
}

void handleCount(const std::vector<Polygon>& polygons, std::istream& is)
{
    std::string arg;
    if (!(is >> arg)) { std::cout << "<INVALID COMMAND>\n"; return; }

    long long count = 0;
    if (arg == "EVEN") {
        count = std::count_if(polygons.begin(), polygons.end(),
            [](const Polygon& p) { return p.points.size() % 2 == 0; });
    } else if (arg == "ODD") {
        count = std::count_if(polygons.begin(), polygons.end(),
            [](const Polygon& p) { return p.points.size() % 2 != 0; });
    } else {
        try {
            long long num = std::stoll(arg);
            if (num < 3) { std::cout << "<INVALID COMMAND>\n"; return; }
            count = std::count_if(polygons.begin(), polygons.end(),
                [num](const Polygon& p) {
                    return p.points.size() == static_cast<size_t>(num);
                });
        } catch (...) {
            std::cout << "<INVALID COMMAND>\n";
            return;
        }
    }
    std::cout << count << "\n";
}

void handleRects(const std::vector<Polygon>& polygons, std::istream&)
{
    long long count = std::count_if(polygons.begin(), polygons.end(), isRectangle);
    std::cout << count << "\n";
}

void handleIntersections(const std::vector<Polygon>& polygons, std::istream& is)
{
    std::string line_remainder;
    std::getline(is, line_remainder);

    Polygon target;
    if (!parsePolygonFromString(line_remainder, target)) {
        std::cout << "<INVALID COMMAND>\n";
        return;
    }

    long long count = std::count_if(polygons.begin(), polygons.end(),
        [&target](const Polygon& p) { return doPolygonsIntersect(p, target); });
    std::cout << count << "\n";
}
