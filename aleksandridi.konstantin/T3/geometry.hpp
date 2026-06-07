#ifndef GEOMETRY_HPP
#define GEOMETRY_HPP

#include <vector>
#include <iostream>

struct Point {
	int x, y;
	bool operator==(const Point& other) const {
		return x == other.x && y == other.y;
	}
};

struct Polygon {
	std::vector<Point> points;
	bool operator==(const Polygon& other) const {
		return points == other.points;
	}
};

double getArea(const Polygon& p);
bool parsePolygon(const std::string& line, Polygon& p);

#endif //GEOMETRY_HPP
