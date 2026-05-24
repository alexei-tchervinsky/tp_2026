#ifndef PARSING_HPP
#define PARSING_HPP

#include <string>
#include "geometry.hpp"

bool parsePoint(const std::string& s, Point& pt);
bool parsePolygonLine(const std::string& line, Polygon& poly);
bool parsePolygonFromString(const std::string& str, Polygon& poly);

#endif
