#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include "geometry.hpp"
#include <vector>
#include <string>

void cmdArea(const std::vector<Polygon>& polygons, const std::string& arg);
void cmdMax(const std::vector<Polygon>& polygons, const std::string& arg);
void cmdMin(const std::vector<Polygon>& polygons, const std::string& arg);
void cmdCount(const std::vector<Polygon>& polygons, const std::string& arg);
void cmdLessArea(const std::vector<Polygon>& polygons, const Polygon& p);
void cmdMaxSeq(const std::vector<Polygon>& polygons, const Polygon& p);

#endif //COMMANDS_HPP
