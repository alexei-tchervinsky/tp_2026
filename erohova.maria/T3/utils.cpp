#include "utils.hpp"
#include <sstream>
#include <fstream>
#include <algorithm>

bool readPoint(std::istream& is, Point& pt) {
    char c1, c2, c3;
    if (is >> c1 >> pt.x >> c2 >> pt.y >> c3) {
        if (c1 == '(' && c2 == ';' && c3 == ')') {
            return true;
        }
    }
    is.clear();
    return false;
}

bool parsePolygon(const std::string& line, Polygon& polygon) {
    std::stringstream ss(line);
    size_t vertexesCount;
    if (!(ss >> vertexesCount)) return false;

    if (vertexesCount < 3) return false;

    std::vector<Point> tempPoints;
    tempPoints.reserve(vertexesCount);

    for (size_t i = 0; i < vertexesCount; ++i) {
        Point pt;
        if (!readPoint(ss, pt)) {
            return false;
        }
        tempPoints.push_back(pt);
    }

    std::string trailing;
    if (ss >> trailing) {
        return false;
    }

    polygon.points = std::move(tempPoints);
    return true;
}

std::vector<Polygon> loadPolygonsFromFile(const std::string& filename) {
    std::ifstream file(filename);
    std::vector<Polygon> polygons;
    if (!file.is_open()) return polygons;

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;

        Polygon poly;
        if (parsePolygon(line, poly)) {
            polygons.push_back(poly);
        }
    }
    return polygons;
}
