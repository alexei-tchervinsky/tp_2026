#ifndef UTILS_HPP
#define UTILS_HPP

#include <vector>
#include <string>
#include <cstddef>
#include "geometry.hpp"

std::vector<Polygon> readPolygons(const std::string& filename);
bool parsePolygon(std::istream& is, Polygon& out);
void setupIomanip(std::ostream &os);

struct PolygonEqual
{
    bool operator()(const Polygon& a, const Polygon& b) const { return a == b; }
};

bool isUnsignedNumber(const std::string &value);
double areaEvenOdd(const std::vector<Polygon>& data, bool odd);
double areaMean(const std::vector<Polygon>& data);
double areaNum(const std::vector<Polygon>& data, std::size_t num_of_vertexes);
double maxArea(const std::vector<Polygon>& data);
double minArea(const std::vector<Polygon>& data);
std::size_t maxVertexes(const std::vector<Polygon>& data);
std::size_t minVertexes(const std::vector<Polygon>& data);

void cmdArea(const std::vector<Polygon>& data, std::istream& is, std::ostream& os);
void cmdMax(const std::vector<Polygon>& data, std::istream& is, std::ostream& os);
void cmdMin(const std::vector<Polygon>& data, std::istream& is, std::ostream& os);
void cmdCount(const std::vector<Polygon>& data, std::istream& is, std::ostream& os);
void cmdEcho(std::vector<Polygon>& data, std::istream& is, std::ostream& os);
void cmdRightshapes(const std::vector<Polygon>& data, std::istream& is, std::ostream& os);

#endif
