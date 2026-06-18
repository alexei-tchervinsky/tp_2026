#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <regex>
#include <numeric>
#include <algorithm>
#include <iomanip>
#include <sstream>

struct Point {
    int x, y;
    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }
};

struct Polygon {
    std::vector<Point> points;
    double area = 0.0;
    bool operator==(const Polygon& other) const {
        if (points.size() != other.points.size()) return false;
        return std::equal(
            points.begin(), points.end(), other.points.begin()
        );
    }
};

double calculateArea(const std::vector<Point>& points) {
    if (points.size() < 3) return 0.0;
    std::vector<size_t> indices(points.size());
    std::iota(indices.begin(), indices.end(), 0);

    auto areaCalc = [&](double acc, size_t i) {
        size_t next = (i + 1) % points.size();
        return acc + (points[i].x * points[next].y -
                      points[next].x * points[i].y);
    };

    double area = std::accumulate(
        indices.begin(), indices.end(), 0.0, areaCalc
    );
    return std::abs(area) / 2.0;
}

bool hasRightAngle(const Polygon& polygon) {
    if (polygon.points.size() < 3) return false;
    std::vector<size_t> indices(polygon.points.size());
    std::iota(indices.begin(), indices.end(), 0);

    auto checkAngle = [&](size_t i) {
        size_t prev = (i == 0) ? polygon.points.size() - 1 : i - 1;
        size_t next = (i + 1) % polygon.points.size();
        long long dx1 = polygon.points[i].x - polygon.points[prev].x;
        long long dy1 = polygon.points[i].y - polygon.points[prev].y;
        long long dx2 = polygon.points[next].x - polygon.points[i].x;
        long long dy2 = polygon.points[next].y - polygon.points[i].y;
        return dx1 * dx2 + dy1 * dy2 == 0;
    };

    return std::any_of(
        indices.begin(), indices.end(), checkAngle
    );
}

bool parsePolygon(const std::string& line, Polygon& out) {
    static const std::regex re(
        R"(^\s*(\d+)\s*((?:\s*\(-?\d+;-?\d+\)\s*)+)\s*$)"
    );
    static const std::regex pointRe(
        R"(\(\s*(-?\d+)\s*;\s*(-?\d+)\s*\))"
    );

    std::smatch match;
    if (!std::regex_match(line, match, re)) {
        return false;
    }

    int n = std::stoi(match[1].str());

    // Фигура должна иметь минимум 3 вершины
    if (n < 3) {
        return false;
    }

    std::string coords = match[2].str();

    auto points_begin = std::sregex_iterator(
        coords.begin(), coords.end(), pointRe
    );
    auto points_end = std::sregex_iterator();

    std::vector<Point> points;
    points.reserve(n);

    auto parsePoint = [](const std::smatch& m) {
        return Point{
            std::stoi(m[1].str()),
            std::stoi(m[2].str())
        };
    };

    std::transform(
        points_begin, points_end,
        std::back_inserter(points), parsePoint
    );

    if (points.size() != static_cast<size_t>(n)) {
        return false;
    }

    out.points = std::move(points);
    out.area = calculateArea(out.points);
    return true;
}

struct EchoInserter {
    std::vector<Polygon>& vec;
    const Polygon& target;
    int& count;

    EchoInserter& operator=(const Polygon& p) {
        vec.push_back(p);
        if (p == target) {
            vec.push_back(p);
            count++;
        }
        return *this;
    }
    EchoInserter& operator*() { return *this; }
    EchoInserter& operator++() { return *this; }
    EchoInserter& operator++(int) { return *this; }
};

void processCommand(
    const std::string& line,
    std::vector<Polygon>& polygons
) {
    std::stringstream ss(line);
    std::string cmd, arg1;
    if (!(ss >> cmd)) return;

    bool valid = true;

    if (cmd == "AREA") {
        if (ss >> arg1) {
            if (arg1 == "EVEN") {
                auto isEven = [](double acc, const Polygon& p) {
                    return acc + (p.points.size() % 2 == 0 ?
                                  p.area : 0.0);
                };
                double sum = std::accumulate(
                    polygons.begin(), polygons.end(), 0.0, isEven
                );
                std::cout << sum << "\n";
            }
            else if (arg1 == "ODD") {
                auto isOdd = [](double acc, const Polygon& p) {
                    return acc + (p.points.size() % 2 != 0 ?
                                  p.area : 0.0);
                };
                double sum = std::accumulate(
                    polygons.begin(), polygons.end(), 0.0, isOdd
                );
                std::cout << sum << "\n";
            }
            else if (arg1 == "MEAN") {
                // Если фигур нет — невалидная команда
                if (polygons.empty()) {
                    valid = false;
                } else {
                    auto sumArea = [](double acc, const Polygon& p) {
                        return acc + p.area;
                    };
                    double sum = std::accumulate(
                        polygons.begin(), polygons.end(),
                        0.0, sumArea
                    );
                    std::cout << (sum / polygons.size()) << "\n";
                }
            }
            else {
                try {
                    int num = std::stoi(arg1);
                    // Количество вершин должно быть >= 3
                    if (num < 3) {
                        valid = false;
                    } else {
                        size_t sz = static_cast<size_t>(num);
                        auto matchCount = [sz](double acc, const Polygon& p) {
                            return acc + (p.points.size() == sz ?
                                          p.area : 0.0);
                        };
                        double sum = std::accumulate(
                            polygons.begin(), polygons.end(),
                            0.0, matchCount
                        );
                        std::cout << sum << "\n";
                    }
                } catch (...) {
                    valid = false;
                }
            }
        } else {
            valid = false;
        }
    }
    else if (cmd == "MAX") {
        if (ss >> arg1) {
            // Если фигур нет — невалидная команда
            if (polygons.empty()) {
                valid = false;
            }
            else if (arg1 == "AREA") {
                auto cmpArea = [](const Polygon& a, const Polygon& b) {
                    return a.area < b.area;
                };
                auto it = std::max_element(
                    polygons.begin(), polygons.end(), cmpArea
                );
                std::cout << it->area << "\n";
            }
            else if (arg1 == "VERTEXES") {
                auto cmpSize = [](const Polygon& a, const Polygon& b) {
                    return a.points.size() < b.points.size();
                };
                auto it = std::max_element(
                    polygons.begin(), polygons.end(), cmpSize
                );
                std::cout << it->points.size() << "\n";
            }
            else {
                valid = false;
            }
        } else {
            valid = false;
        }
    }
    else if (cmd == "MIN") {
        if (ss >> arg1) {
            // Если фигур нет — невалидная команда
            if (polygons.empty()) {
                valid = false;
            }
            else if (arg1 == "AREA") {
                auto cmpArea = [](const Polygon& a, const Polygon& b) {
                    return a.area < b.area;
                };
                auto it = std::min_element(
                    polygons.begin(), polygons.end(), cmpArea
                );
                std::cout << it->area << "\n";
            }
            else if (arg1 == "VERTEXES") {
                auto cmpSize = [](const Polygon& a, const Polygon& b) {
                    return a.points.size() < b.points.size();
                };
                auto it = std::min_element(
                    polygons.begin(), polygons.end(), cmpSize
                );
                std::cout << it->points.size() << "\n";
            }
            else {
                valid = false;
            }
        } else {
            valid = false;
        }
    }
    else if (cmd == "COUNT") {
        if (ss >> arg1) {
            if (arg1 == "EVEN") {
                auto isEven = [](const Polygon& p) {
                    return p.points.size() % 2 == 0;
                };
                int count = std::count_if(
                    polygons.begin(), polygons.end(), isEven
                );
                std::cout << count << "\n";
            }
            else if (arg1 == "ODD") {
                auto isOdd = [](const Polygon& p) {
                    return p.points.size() % 2 != 0;
                };
                int count = std::count_if(
                    polygons.begin(), polygons.end(), isOdd
                );
                std::cout << count << "\n";
            }
            else {
                try {
                    int num = std::stoi(arg1);
                    // Количество вершин должно быть >= 3
                    if (num < 3) {
                        valid = false;
                    } else {
                        size_t sz = static_cast<size_t>(num);
                        auto matchCount = [sz](const Polygon& p) {
                            return p.points.size() == sz;
                        };
                        int count = std::count_if(
                            polygons.begin(), polygons.end(), matchCount
                        );
                        std::cout << count << "\n";
                    }
                } catch (...) {
                    valid = false;
                }
            }
        } else {
            valid = false;
        }
    }
    else if (cmd == "ECHO") {
        std::string rest;
        std::getline(ss, rest);
        rest.erase(0, rest.find_first_not_of(" \t"));
        if (!rest.empty()) {
            rest.erase(rest.find_last_not_of(" \t") + 1);
        }

        Polygon target;
        bool ok = parsePolygon(rest, target);
        if (ok) {
            std::vector<Polygon> new_polygons;
            new_polygons.reserve(polygons.size() * 2);
            int count = 0;

            std::copy(
                polygons.begin(), polygons.end(),
                EchoInserter{new_polygons, target, count}
            );
            polygons = std::move(new_polygons);
            std::cout << count << "\n";
        } else {
            valid = false;
        }
    }
    else if (cmd == "RIGHTSHAPES") {
        auto hasRight = [](const Polygon& p) {
            return hasRightAngle(p);
        };
        int count = std::count_if(
            polygons.begin(), polygons.end(), hasRight
        );
        std::cout << count << "\n";
    }
    else {
        valid = false;
    }

    if (!valid) {
        std::cout << "<INVALID COMMAND>\n";
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Error: filename not provided\n";
        return 1;
    }

    std::ifstream file(argv[1]);
    if (!file.is_open()) {
        std::cerr << "Error: cannot open file\n";
        return 1;
    }

    std::vector<Polygon> polygons;
    std::string line;

    while (std::getline(file, line)) {
        line.erase(0, line.find_first_not_of(" \t\r\n"));
        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }
        line.erase(line.find_last_not_of(" \t\r\n") + 1);
        if (line.empty()) continue;

        Polygon p;
        if (parsePolygon(line, p)) {
            polygons.push_back(std::move(p));
        }
    }
    file.close();

    std::cout << std::fixed << std::setprecision(1);

    while (std::getline(std::cin, line)) {
        if (line.empty()) continue;
        processCommand(line, polygons);
    }

    return 0;
}
