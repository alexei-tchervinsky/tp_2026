#include "Commands.hpp"
#include <algorithm>
#include <numeric>
#include <iostream>
#include <iomanip>
#include <string>
#include <functional>
#include <cmath>
#include <map>

// площадь
double getArea(const Polygon& polygon) {
    if (polygon.points.size() < 3) return 0.0;

    auto num_points = polygon.points.size();
    double area = std::accumulate(polygon.points.begin(), polygon.points.end(), 0.0,
        [&polygon, num_points, idx = 0](double sum, const Point& curr) mutable {
            const Point& next = polygon.points[(idx + 1) % num_points];
            idx++;
            return sum + (curr.x * next.y - next.x * curr.y);
        });

    return std::abs(area) / 2.0;
}

bool isEven(const Polygon& p) { return p.points.size() % 2 == 0; }
bool isOdd(const Polygon& p) { return p.points.size() % 2 != 0; }
bool hasVertices(const Polygon& p, size_t num) { return p.points.size() == num; }

void handleArea(const std::vector<Polygon>& polygons) {
    std::string arg;
    std::cin >> arg;
    double total_area = 0.0;

    if (arg == "EVEN") {
        total_area = std::accumulate(polygons.begin(), polygons.end(), 0.0,
            [](double sum, const Polygon& p) { return sum + (isEven(p) ? getArea(p) : 0.0); });
    } else if (arg == "ODD") {
        total_area = std::accumulate(polygons.begin(), polygons.end(), 0.0,
            [](double sum, const Polygon& p) { return sum + (isOdd(p) ? getArea(p) : 0.0); });
    } else if (arg == "MEAN") {
        if (polygons.empty()) {
            std::cout << "<INVALID COMMAND>\n";
            return;
        }
        double sum_area = std::accumulate(polygons.begin(), polygons.end(), 0.0,
            [](double sum, const Polygon& p) { return sum + getArea(p); });
        total_area = sum_area / polygons.size();
    } else {
        try {
            size_t num = std::stoull(arg);
            if (num < 3) throw std::invalid_argument("");
            total_area = std::accumulate(polygons.begin(), polygons.end(), 0.0,
                [num](double sum, const Polygon& p) { return sum + (hasVertices(p, num) ? getArea(p) : 0.0); });
        } catch (...) {
            std::cout << "<INVALID COMMAND>\n";
            return;
        }
    }
    std::cout << std::fixed << std::setprecision(1) << total_area << "\n";
}

void handleMax(const std::vector<Polygon>& polygons) {
    std::string arg;
    std::cin >> arg;
    if (polygons.empty()) {
        std::cout << "<INVALID COMMAND>\n";
        return;
    }

    if (arg == "AREA") {
        auto it = std::max_element(polygons.begin(), polygons.end(),
            [](const Polygon& a, const Polygon& b) { return getArea(a) < getArea(b); });
        std::cout << std::fixed << std::setprecision(1) << getArea(*it) << "\n";
    } else if (arg == "VERTEXES") {
        auto it = std::max_element(polygons.begin(), polygons.end(),
            [](const Polygon& a, const Polygon& b) { return a.points.size() < b.points.size(); });
        std::cout << it->points.size() << "\n";
    } else {
        std::cout << "<INVALID COMMAND>\n";
    }
}

void handleMin(const std::vector<Polygon>& polygons) {
    std::string arg;
    std::cin >> arg;
    if (polygons.empty()) {
        std::cout << "<INVALID COMMAND>\n";
        return;
    }

    if (arg == "AREA") {
        auto it = std::min_element(polygons.begin(), polygons.end(),
            [](const Polygon& a, const Polygon& b) { return getArea(a) < getArea(b); });
        std::cout << std::fixed << std::setprecision(1) << getArea(*it) << "\n";
    } else if (arg == "VERTEXES") {
        auto it = std::min_element(polygons.begin(), polygons.end(),
            [](const Polygon& a, const Polygon& b) { return a.points.size() < b.points.size(); });
        std::cout << it->points.size() << "\n";
    } else {
        std::cout << "<INVALID COMMAND>\n";
    }
}

void handleCount(const std::vector<Polygon>& polygons) {
    std::string arg;
    std::cin >> arg;
    long long count = 0;

    if (arg == "EVEN") {
        count = std::count_if(polygons.begin(), polygons.end(), isEven);
    } else if (arg == "ODD") {
        count = std::count_if(polygons.begin(), polygons.end(), isOdd);
    } else {
        try {
            size_t num = std::stoull(arg);
            if (num < 3) { // <-- test count
                std::cout << "<INVALID COMMAND>\n";
                return;
            }
            count = std::count_if(polygons.begin(), polygons.end(), [num](const Polygon& p) { return hasVertices(p, num); });
        } catch (...) {
            std::cout << "<INVALID COMMAND>\n";
            return;
        }
    }
    std::cout << count << "\n";
}

void handlePerms(const std::vector<Polygon>& polygons) {
    Polygon target;
    if (!(std::cin >> target)) {
        std::cout << "<INVALID COMMAND>\n";
        std::cin.clear();
        std::string dummy;
        std::getline(std::cin, dummy);
        return;
    }

    std::string extra;
    std::getline(std::cin, extra);
    if (!extra.empty() && std::any_of(extra.begin(), extra.end(), [](char c) { return c == '('; })) {
        std::cout << "<INVALID COMMAND>\n";
        return;
    }

    auto point_eq = [](const Point& a, const Point& b) {
        return a.x == b.x && a.y == b.y;
    };

    long long count = std::count_if(polygons.begin(), polygons.end(), [&](const Polygon& p) {
        if (p.points.size() != target.points.size()) {
            return false;
        }
        return std::is_permutation(p.points.begin(), p.points.end(), target.points.begin(), point_eq);
    });

    std::cout << count << "\n";
}

void handleSame(const std::vector<Polygon>& polygons) {
    Polygon target;
    if (!(std::cin >> target)) {
        std::cout << "<INVALID COMMAND>\n";
        std::cin.clear();
        std::string dummy;
        std::getline(std::cin, dummy);
        return;
    }

    // test (лишние точки в строке)
    std::string extra;
    std::getline(std::cin, extra);
    if (!extra.empty() && std::any_of(extra.begin(), extra.end(), [](char c) { return c == '(' || c == ';'; })) {
        std::cout << "<INVALID COMMAND>\n";
        return;
    }

    long long count = std::count_if(polygons.begin(), polygons.end(), [&](const Polygon& p) {
        if (p.points.size() != target.points.size()) {
            return false;
        }

        int dx = p.points[0].x - target.points[0].x;
        int dy = p.points[0].y - target.points[0].y;

        return std::equal(p.points.begin(), p.points.end(), target.points.begin(),
            [dx, dy](const Point& a, const Point& b) {
                return (a.x - b.x == dx) && (a.y - b.y == dy);
            });
    });

    std::cout << count << "\n";
}

void doTasks(const std::vector<Polygon>& polygons) {
    std::map<std::string, std::function<void(void)>> cmds;

    cmds["AREA"]  = [&polygons]() { handleArea(polygons); };
    cmds["MAX"]   = [&polygons]() { handleMax(polygons); };
    cmds["MIN"]   = [&polygons]() { handleMin(polygons); };
    cmds["COUNT"] = [&polygons]() { handleCount(polygons); };
    cmds["PERMS"] = [&polygons]() { handlePerms(polygons); };
    cmds["SAME"]  = [&polygons]() { handleSame(polygons); };

    std::string command;

    while (!(std::cin >> command).eof()) {
        try {
            cmds.at(command)();
        } catch (...) {
            std::cout << "<INVALID COMMAND>\n";

            std::string dummy;
            std::getline(std::cin, dummy);
        }
    }
}
