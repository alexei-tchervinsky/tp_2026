#ifndef GEOMETRY_HPP
#define GEOMETRY_HPP

#include <cstddef>
#include <iosfwd>
#include <string>
#include <vector>

struct Point
{
  int x;
  int y;
};

struct Polygon
{
  std::vector< Point > points;
};

bool operator==(const Point& lhs, const Point& rhs);
bool operator!=(const Point& lhs, const Point& rhs);
bool operator==(const Polygon& lhs, const Polygon& rhs);
bool operator!=(const Polygon& lhs, const Polygon& rhs);

std::istream& operator>>(std::istream& input, Point& point);
std::ostream& operator<<(std::ostream& output, const Point& point);
std::istream& operator>>(std::istream& input, Polygon& polygon);
std::ostream& operator<<(std::ostream& output, const Polygon& polygon);

double getArea(const Polygon& polygon);
std::vector< Polygon > readPolygons(const std::string& filename);

std::size_t removeEchoes(std::vector< Polygon >& polygons, const Polygon& polygon);
bool isInFrame(const std::vector< Polygon >& polygons, const Polygon& polygon);

void executeCommand(
    const std::string& command,
    std::vector< Polygon >& polygons,
    std::ostream& output);

void processCommands(
    std::istream& input,
    std::vector< Polygon >& polygons,
    std::ostream& output);

#endif
