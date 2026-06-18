#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <numeric>
#include <functional>
#include <iomanip>

#include "polygon.hpp"
#include "utils.hpp"
#include "iofmtguard.hpp"

void handleArea(const std::vector<Polygon>& dataset, std::istream& is) {
    std::string arg;
    if (!(is >> arg)) {
        std::cout << "<INVALID COMMAND>\n";
        return;
    }

    std::string trailing;
    if (is >> trailing) {
        std::cout << "<INVALID COMMAND>\n";
        return;
    }

    iofmtguard guard(std::cout);
    std::cout << std::fixed << std::setprecision(1);

    double totalArea = 0.0;
    if (arg == "EVEN") {
        totalArea = std::accumulate(dataset.begin(), dataset.end(), 0.0, [](double sum, const Polygon& p) {
            return sum + (p.points.size() % 2 == 0 ? getArea(p) : 0.0);
        });
    } else if (arg == "ODD") {
        totalArea = std::accumulate(dataset.begin(), dataset.end(), 0.0, [](double sum, const Polygon& p) {
            return sum + (p.points.size() % 2 != 0 ? getArea(p) : 0.0);
        });
    } else if (arg == "MEAN") {
        if (dataset.empty()) {
            std::cout << "<INVALID COMMAND>\n";
            return;
        }
        double sum = std::accumulate(dataset.begin(), dataset.end(), 0.0, [](double s, const Polygon& p) {
            return s + getArea(p);
        });
        totalArea = sum / dataset.size();
    } else {
        try {
            size_t targetSize = std::stoull(arg);
            if (targetSize < 3) {
                std::cout << "<INVALID COMMAND>\n";
                return;
            }
            totalArea = std::accumulate(dataset.begin(), dataset.end(), 0.0, [=](double sum, const Polygon& p) {
                return sum + (p.points.size() == targetSize ? getArea(p) : 0.0);
            });
        } catch (...) {
            std::cout << "<INVALID COMMAND>\n";
            return;
        }
    }
    std::cout << totalArea << "\n";
}

void handleMax(const std::vector<Polygon>& dataset, std::istream& is) {
    std::string arg;
    if (!(is >> arg) || dataset.empty()) {
        std::cout << "<INVALID COMMAND>\n";
        return;
    }

    std::string trailing;
    if (is >> trailing) {
        std::cout << "<INVALID COMMAND>\n";
        return;
    }

    if (arg == "AREA") {
        auto it = std::max_element(dataset.begin(), dataset.end(), [](const Polygon& a, const Polygon& b) {
            return getArea(a) < getArea(b);
        });
        iofmtguard guard(std::cout);
        std::cout << std::fixed << std::setprecision(1) << getArea(*it) << "\n";
    } else if (arg == "VERTEXES") {
        auto it = std::max_element(dataset.begin(), dataset.end(), [](const Polygon& a, const Polygon& b) {
            return a.points.size() < b.points.size();
        });
        std::cout << it->points.size() << "\n";
    } else {
        std::cout << "<INVALID COMMAND>\n";
    }
}

void handleMin(const std::vector<Polygon>& dataset, std::istream& is) {
    std::string arg;
    if (!(is >> arg) || dataset.empty()) {
        std::cout << "<INVALID COMMAND>\n";
        return;
    }

    std::string trailing;
    if (is >> trailing) {
        std::cout << "<INVALID COMMAND>\n";
        return;
    }

    if (arg == "AREA") {
        auto it = std::min_element(dataset.begin(), dataset.end(), [](const Polygon& a, const Polygon& b) {
            return getArea(a) < getArea(b);
        });
        iofmtguard guard(std::cout);
        std::cout << std::fixed << std::setprecision(1) << getArea(*it) << "\n";
    } else if (arg == "VERTEXES") {
        auto it = std::min_element(dataset.begin(), dataset.end(), [](const Polygon& a, const Polygon& b) {
            return a.points.size() < b.points.size();
        });
        std::cout << it->points.size() << "\n";
    } else {
        std::cout << "<INVALID COMMAND>\n";
    }
}

void handleCount(const std::vector<Polygon>& dataset, std::istream& is) {
    std::string arg;
    if (!(is >> arg)) {
        std::cout << "<INVALID COMMAND>\n";
        return;
    }

    std::string trailing;
    if (is >> trailing) {
        std::cout << "<INVALID COMMAND>\n";
        return;
    }

    long long count = 0;
    if (arg == "EVEN") {
        count = std::count_if(dataset.begin(), dataset.end(), [](const Polygon& p) {
            return p.points.size() % 2 == 0;
        });
    } else if (arg == "ODD") {
        count = std::count_if(dataset.begin(), dataset.end(), [](const Polygon& p) {
            return p.points.size() % 2 != 0;
        });
    } else {
        try {
            size_t targetSize = std::stoull(arg);
            if (targetSize < 3) {
                std::cout << "<INVALID COMMAND>\n";
                return;
            }
            count = std::count_if(dataset.begin(), dataset.end(), [=](const Polygon& p) {
                return p.points.size() == targetSize;
            });
        } catch (...) {
            std::cout << "<INVALID COMMAND>\n";
            return;
        }
    }
    std::cout << count << "\n";
}

void handlePerms(const std::vector<Polygon>& dataset, std::istream& is) {
    std::string remainder;
    std::getline(is, remainder);

    Polygon targetPoly;
    if (!parsePolygon(remainder, targetPoly)) {
        std::cout << "<INVALID COMMAND>\n";
        return;
    }

    if (targetPoly.points.size() < 3) {
        std::cout << "<INVALID COMMAND>\n";
        return;
    }

    long long count = std::count_if(dataset.begin(), dataset.end(), std::bind(isPermutation, std::placeholders::_1, targetPoly));
    std::cout << count << "\n";
}

void handleRightShapes(const std::vector<Polygon>& dataset) {
    long long count = std::count_if(dataset.begin(), dataset.end(), hasRightAngle);
    std::cout << count << "\n";
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Error: Invalid arguments.\n";
        return 1;
    }

    std::string filename = argv[1];
    std::vector<Polygon> dataset = loadPolygonsFromFile(filename);

    std::string line;
    while (std::getline(std::cin, line)) {
        if (line.empty()) continue;

        std::stringstream ss(line);
        std::string command;
        ss >> command;

        if (command == "AREA") {
            handleArea(dataset, ss);
        } else if (command == "MAX") {
            handleMax(dataset, ss);
        } else if (command == "MIN") {
            handleMin(dataset, ss);
        } else if (command == "COUNT") {
            handleCount(dataset, ss);
        } else if (command == "PERMS") {
            handlePerms(dataset, ss);
        } else if (command == "RIGHTSHAPES") {
            std::string trailing;
            if (ss >> trailing) {
                std::cout << "<INVALID COMMAND>\n";
            } else {
                handleRightShapes(dataset);
            }
        } else {
            std::cout << "<INVALID COMMAND>\n";
        }
    }

    return 0;
}
