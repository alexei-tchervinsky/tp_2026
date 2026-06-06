#include "Commands.h"
#include "Geometry.h"
#include <iostream>
#include <numeric>
#include <algorithm>
#include <iomanip>
#include <stdexcept>

// Вспомогательная функция для проверки, что в строке не осталось лишних данных
void validateEnd(std::stringstream& ss) {
    std::string extra;
    if (ss >> extra) throw std::runtime_error("");
}

void cmdArea(const std::vector<Polygon>& figures, std::stringstream& ss) {
    std::string arg;
    if (!(ss >> arg)) throw std::runtime_error("");
    double res = 0;
    if (arg == "EVEN") {
        res = std::accumulate(figures.begin(), figures.end(), 0.0, [](double s, const Polygon& p) {
            return (p.points.size() % 2 == 0) ? s + getArea(p) : s;
        });
    } else if (arg == "ODD") {
        res = std::accumulate(figures.begin(), figures.end(), 0.0, [](double s, const Polygon& p) {
            return (p.points.size() % 2 != 0) ? s + getArea(p) : s;
        });
    } else if (arg == "MEAN") {
        if (figures.empty()) throw std::runtime_error("");
        res = std::accumulate(figures.begin(), figures.end(), 0.0, [](double s, const Polygon& p) {
            return s + getArea(p);
        }) / static_cast<double>(figures.size());
    } else {
        if (!std::all_of(arg.begin(), arg.end(), ::isdigit)) throw std::runtime_error("");
        size_t n = std::stoul(arg);
        if (n < 3) throw std::runtime_error("");
        res = std::accumulate(figures.begin(), figures.end(), 0.0, [n](double s, const Polygon& p) {
            return (p.points.size() == n) ? s + getArea(p) : s;
        });
    }
    validateEnd(ss);
    std::cout << std::fixed << std::setprecision(1) << res << "\n";
}

void cmdMax(const std::vector<Polygon>& figures, std::stringstream& ss) {
    if (figures.empty()) throw std::runtime_error("");
    std::string arg;
    if (!(ss >> arg)) throw std::runtime_error("");
    validateEnd(ss);
    if (arg == "AREA") {
        auto it = std::max_element(figures.begin(), figures.end(), [](const Polygon& a, const Polygon& b) {
            return getArea(a) < getArea(b);
        });
        std::cout << std::fixed << std::setprecision(1) << getArea(*it) << "\n";
    } else if (arg == "VERTEXES") {
        auto it = std::max_element(figures.begin(), figures.end(), [](const Polygon& a, const Polygon& b) {
            return a.points.size() < b.points.size();
        });
        std::cout << it->points.size() << "\n";
    } else throw std::runtime_error("");
}

void cmdMin(const std::vector<Polygon>& figures, std::stringstream& ss) {
    if (figures.empty()) throw std::runtime_error("");
    std::string arg;
    if (!(ss >> arg)) throw std::runtime_error("");
    validateEnd(ss);
    if (arg == "AREA") {
        auto it = std::min_element(figures.begin(), figures.end(), [](const Polygon& a, const Polygon& b) {
            return getArea(a) < getArea(b);
        });
        std::cout << std::fixed << std::setprecision(1) << getArea(*it) << "\n";
    } else if (arg == "VERTEXES") {
        auto it = std::min_element(figures.begin(), figures.end(), [](const Polygon& a, const Polygon& b) {
            return a.points.size() < b.points.size();
        });
        std::cout << it->points.size() << "\n";
    } else throw std::runtime_error("");
}

void cmdCount(const std::vector<Polygon>& figures, std::stringstream& ss) {
    std::string arg;
    if (!(ss >> arg)) throw std::runtime_error("");
    size_t res = 0;
    if (arg == "EVEN") {
        res = std::count_if(figures.begin(), figures.end(), [](const Polygon& p) { return p.points.size() % 2 == 0; });
    } else if (arg == "ODD") {
        res = std::count_if(figures.begin(), figures.end(), [](const Polygon& p) { return p.points.size() % 2 != 0; });
    } else {
        if (!std::all_of(arg.begin(), arg.end(), ::isdigit)) throw std::runtime_error("");
        size_t n = std::stoul(arg);
        if (n < 3) throw std::runtime_error("");
        res = std::count_if(figures.begin(), figures.end(), [n](const Polygon& p) { return p.points.size() == n; });
    }
    validateEnd(ss);
    std::cout << res << "\n";
}

void cmdIntersections(const std::vector<Polygon>& figures, std::stringstream& ss) {
    Polygon target;
    if (!(ss >> target)) throw std::runtime_error("");
    validateEnd(ss);
    std::cout << std::count_if(figures.begin(), figures.end(), [&](const Polygon& p) {
        return polygonsIntersect(p, target);
    }) << "\n";
}

void cmdRmEcho(std::vector<Polygon>& figures, std::stringstream& ss) {
    Polygon target;
    if (!(ss >> target)) throw std::runtime_error("");
    validateEnd(ss);
    size_t initial_size = figures.size();
    auto it = std::unique(figures.begin(), figures.end(), [&](const Polygon& a, const Polygon& b) {
        return (a == target && b == target);
    });
    figures.erase(it, figures.end());
    std::cout << initial_size - figures.size() << "\n";
}
