#ifndef POLYGON_HPP
#define POLYGON_HPP

#include <iostream>
#include <vector>
#include <string>

struct Point {
	int x, y;
};

struct Polygon {
	std::vector<Point> points;
};

// Операторы для парсинга геометрии
std::istream& operator>>(std::istream& in, Point& dest);
std::istream& operator>>(std::istream& in, Polygon& dest);
std::ostream& operator<<(std::ostream& out, const Point& src);

// Вспомогательные функции для работы с полигонами (через алгоритмы)
double getArea(const Polygon& poly);
bool isPointsEqual(const Point& a, const Point& b);
bool isPolygonEqual(const Polygon& a, const Polygon& b);

// Структура для представления bounding box (ограничивающей рамки) всей коллекции
struct Frame {
	Point minPoint;
	Point maxPoint;
};
Frame getCollectionFrame(const std::vector<Polygon>& polygons);
bool isPolygonInFrame(const Polygon& poly, const Frame& frame);

#endif
