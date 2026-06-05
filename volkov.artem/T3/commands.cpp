#include "commands.hpp"

#include <map>
#include <functional>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <numeric>

double sumAreaEven(const std::vector<Polygon> &polygons);

double sumAreaOdd(const std::vector<Polygon> &polygons);

double sumAreaByVertexes(const std::vector<Polygon> &polygons, size_t count);

double meanArea(const std::vector<Polygon> &polygons);

double maxArea(const std::vector<Polygon> &polygons);

double minArea(const std::vector<Polygon> &polygons);

size_t maxVertexes(const std::vector<Polygon> &polygons);

size_t minVertexes(const std::vector<Polygon> &polygons);

size_t countEven(const std::vector<Polygon> &polygons);

size_t countOdd(const std::vector<Polygon> &polygons);

size_t countByVertexes(const std::vector<Polygon> &polygons, size_t count);

size_t echo(std::vector<Polygon> &polygons, const Polygon &polygon);

size_t maxSeq(const std::vector<Polygon> &polygons, const Polygon &polygon);

void printInvalidCommand();

void handleArea(const std::vector<Polygon> &polygons, std::istringstream &in);

void handleMax(const std::vector<Polygon> &polygons, std::istringstream &in);

void handleMin(const std::vector<Polygon> &polygons, std::istringstream &in);

void handleCount(const std::vector<Polygon> &polygons, std::istringstream &in);

void handleEcho(std::vector<Polygon> &polygons, std::istringstream &in);

void handleMaxSeq(const std::vector<Polygon> &polygons, std::istringstream &in);

double sumAreaEven(const std::vector<Polygon> &polygons) {
    return std::accumulate(polygons.begin(), polygons.end(), 0.0,
                           [](double sum, const Polygon &polygon) {
                               if (isEvenVertexes(polygon)) {
                                   return sum + getArea(polygon);
                               }

                               return sum;
                           });
}

double sumAreaOdd(const std::vector<Polygon> &polygons) {
    return std::accumulate(polygons.begin(), polygons.end(), 0.0,
                           [](double sum, const Polygon &polygon) {
                               if (isOddVertexes(polygon)) {
                                   return sum + getArea(polygon);
                               }

                               return sum;
                           });
}

double sumAreaByVertexes(const std::vector<Polygon> &polygons, size_t count) {
    return std::accumulate(polygons.begin(), polygons.end(), 0.0,
                           [count](double sum, const Polygon &polygon) {
                               if (hasVertexCount(polygon, count)) {
                                   return sum + getArea(polygon);
                               }

                               return sum;
                           });
}

double meanArea(const std::vector<Polygon> &polygons) {
    double sum = std::accumulate(polygons.begin(), polygons.end(), 0.0,
                                 [](double currentSum, const Polygon &polygon) {
                                     return currentSum + getArea(polygon);
                                 });

    return sum / polygons.size();
}

double maxArea(const std::vector<Polygon> &polygons) {
    auto iterator = std::max_element(polygons.begin(), polygons.end(),
                                     [](const Polygon &left, const Polygon &right) {
                                         return getArea(left) < getArea(right);
                                     });

    return getArea(*iterator);
}

double minArea(const std::vector<Polygon> &polygons) {
    auto iterator = std::min_element(polygons.begin(), polygons.end(),
                                     [](const Polygon &left, const Polygon &right) {
                                         return getArea(left) < getArea(right);
                                     });

    return getArea(*iterator);
}

size_t maxVertexes(const std::vector<Polygon> &polygons) {
    auto iterator = std::max_element(polygons.begin(), polygons.end(),
                                     [](const Polygon &left, const Polygon &right) {
                                         return left.points.size() < right.points.size();
                                     });

    return iterator->points.size();
}

size_t minVertexes(const std::vector<Polygon> &polygons) {
    auto iterator = std::min_element(polygons.begin(), polygons.end(),
                                     [](const Polygon &left, const Polygon &right) {
                                         return left.points.size() < right.points.size();
                                     });

    return iterator->points.size();
}

size_t countEven(const std::vector<Polygon> &polygons) {
    return std::count_if(polygons.begin(), polygons.end(), isEvenVertexes);
}

size_t countOdd(const std::vector<Polygon> &polygons) {
    return std::count_if(polygons.begin(), polygons.end(), isOddVertexes);
}

size_t countByVertexes(const std::vector<Polygon> &polygons, size_t count) {
    return std::count_if(polygons.begin(), polygons.end(),
                         [count](const Polygon &polygon) {
                             return hasVertexCount(polygon, count);
                         });
}

size_t echo(std::vector<Polygon> &polygons, const Polygon &polygon) {
    size_t added = std::count(polygons.begin(), polygons.end(), polygon);

    std::vector<Polygon> newPolygons;
    newPolygons.reserve(polygons.size() + added);

    for (const Polygon &current: polygons) {
        newPolygons.push_back(current);

        if (current == polygon) {
            newPolygons.push_back(current);
        }
    }

    polygons = newPolygons;
    return added;
}

size_t maxSeq(const std::vector<Polygon> &polygons, const Polygon &polygon) {
    size_t current = 0;
    size_t maximum = 0;

    for (const Polygon &currentPolygon: polygons) {
        if (currentPolygon == polygon) {
            ++current;
            maximum = std::max(maximum, current);
        } else {
            current = 0;
        }
    }

    return maximum;
}

void printInvalidCommand() {
    std::cout << "<INVALID COMMAND>\n";
}

void handleArea(const std::vector<Polygon> &polygons, std::istringstream &in) {
    std::string argument;
    in >> argument;

    if (!in || !isOnlySpaces(in)) {
        printInvalidCommand();
        return;
    }

    if (argument == "EVEN") {
        std::cout << sumAreaEven(polygons) << "\n";
    } else if (argument == "ODD") {
        std::cout << sumAreaOdd(polygons) << "\n";
    } else if (argument == "MEAN") {
        if (polygons.empty()) {
            printInvalidCommand();
            return;
        }

        std::cout << meanArea(polygons) << "\n";
    } else {
        std::istringstream numberStream(argument);
        size_t count = 0;
        numberStream >> count;

        if (!numberStream || !isOnlySpaces(numberStream) || count < 3) {
            printInvalidCommand();
            return;
        }

        std::cout << sumAreaByVertexes(polygons, count) << "\n";
    }
}

void handleMax(const std::vector<Polygon> &polygons, std::istringstream &in) {
    std::string argument;
    in >> argument;

    if (!in || !isOnlySpaces(in) || polygons.empty()) {
        printInvalidCommand();
        return;
    }

    if (argument == "AREA") {
        std::cout << maxArea(polygons) << "\n";
    } else if (argument == "VERTEXES") {
        std::cout << maxVertexes(polygons) << "\n";
    } else {
        printInvalidCommand();
    }
}

void handleMin(const std::vector<Polygon> &polygons, std::istringstream &in) {
    std::string argument;
    in >> argument;

    if (!in || !isOnlySpaces(in) || polygons.empty()) {
        printInvalidCommand();
        return;
    }

    if (argument == "AREA") {
        std::cout << minArea(polygons) << "\n";
    } else if (argument == "VERTEXES") {
        std::cout << minVertexes(polygons) << "\n";
    } else {
        printInvalidCommand();
    }
}

void handleCount(const std::vector<Polygon> &polygons, std::istringstream &in) {
    std::string argument;
    in >> argument;

    if (!in || !isOnlySpaces(in)) {
        printInvalidCommand();
        return;
    }

    if (argument == "EVEN") {
        std::cout << countEven(polygons) << "\n";
    } else if (argument == "ODD") {
        std::cout << countOdd(polygons) << "\n";
    } else {
        std::istringstream numberStream(argument);
        size_t count = 0;
        numberStream >> count;

        if (!numberStream || !isOnlySpaces(numberStream) || count < 3) {
            printInvalidCommand();
            return;
        }

        std::cout << countByVertexes(polygons, count) << "\n";
    }
}

void handleEcho(std::vector<Polygon> &polygons, std::istringstream &in) {
    Polygon polygon;
    in >> polygon;

    if (!in || !isOnlySpaces(in)) {
        printInvalidCommand();
        return;
    }

    std::cout << echo(polygons, polygon) << "\n";
}

void handleMaxSeq(const std::vector<Polygon> &polygons, std::istringstream &in) {
    Polygon polygon;
    in >> polygon;

    if (!in || !isOnlySpaces(in)) {
        printInvalidCommand();
        return;
    }

    std::cout << maxSeq(polygons, polygon) << "\n";
}

void handleCommand(std::vector<Polygon> &polygons, const std::string &line) {
    std::istringstream in(line);
    std::string command;
    in >> command;

    if (!in) {
        printInvalidCommand();
        return;
    }

    std::map<std::string, std::function<void()> > commands;

    commands["AREA"] = [&polygons, &in]() {
        handleArea(polygons, in);
    };

    commands["MAX"] = [&polygons, &in]() {
        handleMax(polygons, in);
    };

    commands["MIN"] = [&polygons, &in]() {
        handleMin(polygons, in);
    };

    commands["COUNT"] = [&polygons, &in]() {
        handleCount(polygons, in);
    };

    commands["ECHO"] = [&polygons, &in]() {
        handleEcho(polygons, in);
    };

    commands["MAXSEQ"] = [&polygons, &in]() {
        handleMaxSeq(polygons, in);
    };

    auto iterator = commands.find(command);

    if (iterator == commands.end()) {
        printInvalidCommand();
        return;
    }

    iterator->second();
}
