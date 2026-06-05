#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <vector>
#include <istream>
#include "geometry.hpp"

void handleArea(const std::vector<Polygon>& polygons, std::istream& is);
void handleMax(const std::vector<Polygon>& polygons, std::istream& is);
void handleMin(const std::vector<Polygon>& polygons, std::istream& is);
void handleCount(const std::vector<Polygon>& polygons, std::istream& is);
void handleRects(const std::vector<Polygon>& polygons, std::istream& is);
void handleIntersections(const std::vector<Polygon>& polygons, std::istream& is);

#endif
