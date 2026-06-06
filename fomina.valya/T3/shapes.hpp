#ifndef SHAPES_HPP
#define SHAPES_HPP

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <numeric>
#include <cmath>

struct Point {
    int x, y;
    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }
};

struct Polygon {
    std::vector<Point> points;
    bool operator==(const Polygon& other) const {
        if (points.size() != other.points.size()) return false;
        return std::equal(points.begin(), points.end(), other.points.begin());
    }
};

double area(const Polygon& p) {
    if (p.points.size() < 3) return 0.0;
    std::vector<Point> shifted = p.points;
    std::rotate(shifted.rbegin(), shifted.rbegin() + 1, shifted.rend());
    return std::abs(std::inner_product(p.points.begin(), p.points.end(), shifted.begin(), 0.0,
                                       std::plus<double>(),
                                       [](const Point& a, const Point& b) {
                                           return static_cast<double>(a.x) * b.y - static_cast<double>(b.x) * a.y;
                                       })) / 2.0;
}

std::istream& operator>>(std::istream& in, Polygon& p) {
    std::string line;
    while (std::getline(in, line)) {
        if (line.empty()) continue;

        std::istringstream iss(line);
        int n;
        if (!(iss >> n) || n <= 0) continue;

        std::string rest;
        std::getline(iss, rest);
        rest.erase(std::remove_if(rest.begin(), rest.end(), ::isspace), rest.end());

        std::vector<Point> pts;
        pts.reserve(n);

        size_t pos = 0;
        bool valid = true;
        for (int i = 0; i < n; ++i) {
            if (pos >= rest.length() || rest[pos] != '(') {
                valid = false;
                break;
            }

            size_t end = rest.find(')', pos);
            if (end == std::string::npos) {
                valid = false;
                break;
            }

            std::string pt_str = rest.substr(pos + 1, end - pos - 1);
            size_t semi = pt_str.find(';');
            if (semi == std::string::npos) {
                valid = false;
                break;
            }

            try {
                int x = std::stoi(pt_str.substr(0, semi));
                int y = std::stoi(pt_str.substr(semi + 1));
                pts.push_back({x, y});
            } catch (...) {
                valid = false;
                break;
            }

            pos = end + 1;
        }

        if (!valid) continue;

        while (pos < rest.length() && std::isspace(rest[pos])) pos++;
        if (pos < rest.length()) continue;

        p.points = std::move(pts);
        return in;
    }
    return in;
}

std::ostream& operator<<(std::ostream& out, const Polygon& p) {
    out << p.points.size();
    for (const auto& pt : p.points) {
        out << "(" << pt.x << ";" << pt.y << ")";
    }
    return out;
}

#endif
