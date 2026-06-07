#ifndef POLYGON_HPP
#define POLYGON_HPP

#include <vector>
#include <iostream>

namespace tchervinsky
{
    struct Point
    {
        int x, y;
        bool operator==(const Point& other) const;
        bool operator!=(const Point& other) const;
        bool operator<(const Point& other) const;
    };

  std::istream& operator>>(std::istream& in, Point& p);
  std::ostream& operator<<(std::ostream& out, const Point& p);

  struct Polygon
  {
    std::vector<Point> points;
    bool operator==(const Polygon& other) const;
  };

  std::istream& operator>>(std::istream& in, Polygon& poly);
  std::ostream& operator<<(std::ostream& out, const Polygon& poly);

  // Вычисление площади фигуры (по формуле Гаусса)
  double getArea(const Polygon& poly);

  // Проверка, является ли фигура прямоугольником
  bool isRectangle(const Polygon& poly);

  // Проверка, содержит ли фигура прямой угол
  bool hasRightAngle(const Polygon& poly);

  // Проверка, лежит ли фигура внутри ограничивающего прямоугольника всех фигур
  bool isInFrame(const Polygon& poly, const std::vector<Polygon>& polygons);

  // Проверка, является ли одна фигура перестановкой другой
  bool isPermutation(const Polygon& a, const Polygon& b);

  // Нахождение ограничивающего прямоугольника (minX, minY, maxX, maxY)
  void getBoundingBox(const std::vector<Polygon>& polygons, int& minX, int& minY, int& maxX, int& maxY);
}

#endif
