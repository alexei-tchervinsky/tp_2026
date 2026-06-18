#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>
#include <vector>
#include <string>
#include "polygon.hpp"

bool readPoint(std::istream& is, Point& pt);
bool parsePolygon(const std::string& line, Polygon& polygon);
std::vector<Polygon> loadPolygonsFromFile(const std::string& filename);

#endif
