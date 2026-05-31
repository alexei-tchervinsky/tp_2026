#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>
#include <string>
#include <vector>

#include "polygon.hpp"

bool parsePolygonArg(std::istream& in, Polygon& poly);

namespace cmd
{
    void AREA(const std::vector<Polygon>& polygons, std::istream& is, std::ostream& os);
    void MAX(const std::vector<Polygon>& polygons, std::istream& is, std::ostream& os);
    void MIN(const std::vector<Polygon>& polygons, std::istream& is, std::ostream& os);
    void COUNT(const std::vector<Polygon>& polygons, std::istream& is, std::ostream& os);
    void INFRAME(const std::vector<Polygon>& polygons, std::istream& is, std::ostream& os);
    void RIGHTSHAPES(const std::vector<Polygon>& polygons, std::istream& is, std::ostream& os);
}

#endif
