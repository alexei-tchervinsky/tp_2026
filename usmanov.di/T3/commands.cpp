#include "commands.h"
#include "ioHandle.h"
#include <iomanip>
#include <string>
#include <iterator>
#include <sstream>
#include <algorithm>
#include <numeric>

void cPrintDouble(double value) {
    std::cout << std::fixed << std::setprecision(1) << value << "\n";
}

void cArea(std::istringstream& iss, const std::vector<Polygon>& polygons) {
    std::string param;
    iss >> param;

    if (param == "EVEN") {
        if (polygons.empty()) {
            cPrintDouble(0.0);
            return;
        }
        auto op = [](const double sum, const Polygon& p) {
            if (p.points_.size() % 2 == 0) {
                return sum + area(p);
            }
            return sum;
        };

        double total = std::accumulate(polygons.begin(), polygons.end(), 0.0, op);
        cPrintDouble(total);
    }
    else if (param == "ODD") {
        if (polygons.empty()) {
            cPrintDouble(0.0);
            return;
        }
        auto op = [](const double sum, const Polygon& p) {
            if (p.points_.size() % 2 == 1) {
                return sum + area(p);
            }
            return sum;
        };

        double total = std::accumulate(polygons.begin(), polygons.end(), 0.0, op);
        cPrintDouble(total);
    }
    else if (param == "MEAN") {
        if (polygons.empty()) {
            std::cout << "<INVALID COMMAND>\n";
            return;
        }
        auto op = [](double sum, const Polygon& p) {
            return sum + area(p);
        };

        double total = std::accumulate(polygons.begin(), polygons.end(), 0.0, op);
        cPrintDouble(total / polygons.size());
    }
    else {
        try {
            int num = std::stoi(param);

            if (num < 3) {
                std::cout << "<INVALID COMMAND>\n";
                return;
            }

            if (polygons.empty()) {
                cPrintDouble(0.0);
                return;
            }

            auto op = [num](double sum, const Polygon& p) {
                if (p.points_.size() == static_cast<size_t>(num)) {
                    return sum + area(p);
                }
                return sum;
                };

            double total = std::accumulate(polygons.begin(), polygons.end(), 0.0, op);
            cPrintDouble(total);
        }
        catch (...) {
            std::cout << "<INVALID COMMAND>\n";
        }
    }
}

void cMax(std::istringstream& iss, const std::vector<Polygon>& polygons) {
    std::string param;
    iss >> param;

    if (polygons.empty()) {
        std::cout << "<INVALID COMMAND>\n";
        return;
    }

    if (param == "AREA") {
        auto op = std::max_element(polygons.begin(), polygons.end(),
            [](const Polygon& a, const Polygon& b) {
                return area(a) < area(b);
            }
        );

        cPrintDouble(area(*op));
    }
    else if (param == "VERTEXES") {
        auto op = std::max_element(polygons.begin(), polygons.end(),
            [](const Polygon& a, const Polygon& b) {
                return a.points_.size() < b.points_.size();
            }
        );

        std::cout << op->points_.size() << "\n";
    }
    else {
        std::cout << "<INVALID COMMAND>\n";
    }
}

void cMin(std::istringstream& iss, const std::vector<Polygon>& polygons) {
    std::string param;
    iss >> param;

    if (polygons.empty()) {
        std::cout << "<INVALID COMMAND>\n";
        return;
    }

    if (param == "AREA") {
        auto op = std::min_element(polygons.begin(), polygons.end(),
            [](const Polygon& a, const Polygon& b) {
                return area(a) < area(b);
            }
        );

        cPrintDouble(area(*op));
    }
    else if (param == "VERTEXES") {
        auto op = std::min_element(polygons.begin(), polygons.end(),
            [](const Polygon& a, const Polygon& b) {
                return a.points_.size() < b.points_.size();
            }
        );

        std::cout << op->points_.size() << "\n";
    }
    else {
        std::cout << "<INVALID COMMAND>\n";
    }
}

void cCount(std::istringstream& iss, const std::vector<Polygon>& polygons) {
    std::string param;
    iss >> param;

    if (param == "EVEN") {
        auto count = std::count_if(polygons.begin(), polygons.end(),
            [](const Polygon& p) {
                return p.points_.size() % 2 == 0;
            }
        );

        std::cout << count << "\n";
    }
    else if (param == "ODD") {
        auto count = std::count_if(polygons.begin(), polygons.end(),
            [](const Polygon& p) {
                return p.points_.size() % 2 == 1;
            }
        );

        std::cout << count << "\n";
    }
    else {
        try {
            int num = std::stoi(param);

            if (num < 3) {
                std::cout << "<INVALID COMMAND>\n";
                return;
            }

            int count = std::count_if(polygons.begin(), polygons.end(),
                [num](const Polygon& p) {
                    return p.points_.size() == static_cast<size_t>(num);
                });

            std::cout << count << "\n";
        }
        catch (...) {
            std::cout << "<INVALID COMMAND>\n";
        }
    }
}

void cRMEcho(std::istringstream& iss, std::vector<Polygon>& polygons) {
    Polygon p;
    iss >> p;

    if (!iss) {
        std::cout << "<INVALID COMMAND>\n";
        return;
    }

    int count = 0;

    auto op = std::unique(polygons.begin(), polygons.end(),
        [&p, &count](const Polygon& a, const Polygon& b) {
            if (a.points_ == p.points_ && b.points_ == p.points_) {
                count++;
                return true;
            }
            return false;
        }
    );

    polygons.erase(op, polygons.end());
    std::cout << count << "\n";
}

void cInFrame(std::istringstream& iss, const std::vector<Polygon>& polygons) {
    Polygon p;
    iss >> p;

    if (!iss) {
        std::cout << "<INVALID COMMAND>\n";
        return;
    }

    if (p.points_.size() < 3) {
        std::cout << "<INVALID COMMAND>\n";
        return;
    }

    char c;
    if (iss >> c) {
        if (c == '(') {
            std::cout << "<INVALID COMMAND>\n";
            return;
        }
    }

    if (polygons.empty()) {
        std::cout << "<FALSE>\n";
        return;
    }

    std::vector<Point> allPoints = std::accumulate(polygons.begin(), polygons.end(),
        std::vector<Point>(),
        [](std::vector<Point> acc, const Polygon& poly) {
            acc.insert(acc.end(), poly.points_.begin(), poly.points_.end());
            return acc;
        }
    );

    auto minX = std::min_element(allPoints.begin(), allPoints.end(),
        [](const Point& a, const Point& b) { return a.x_ < b.x_; });
    auto maxX = std::max_element(allPoints.begin(), allPoints.end(),
        [](const Point& a, const Point& b) { return a.x_ < b.x_; });

    auto minY = std::min_element(allPoints.begin(), allPoints.end(),
        [](const Point& a, const Point& b) { return a.y_ < b.y_; });
    auto maxY = std::max_element(allPoints.begin(), allPoints.end(),
        [](const Point& a, const Point& b) { return a.y_ < b.y_; });

    bool inside = std::all_of(p.points_.begin(), p.points_.end(),
        [&](const Point& p) {
            return p.x_ >= minX->x_ && p.x_ <= maxX->x_ &&
                p.y_ >= minY->y_ && p.y_ <= maxY->y_;
        }
    );

    if (inside) {
        std::cout << "<TRUE>\n";
    }
    else {
        std::cout << "<FALSE>\n";
    }
}
