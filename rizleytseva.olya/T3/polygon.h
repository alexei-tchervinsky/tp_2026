#ifndef POLYGON_H
#define POLYGON_H

#include <iostream>
#include <vector>
#include <string>

// ---- Структуры данных ----

struct Point
{
  int x, y;

  bool operator==(const Point& other) const;
  bool operator<(const Point& other) const; // для sort при PERMS
};

struct Polygon
{
  std::vector< Point > points;

  bool operator==(const Polygon& other) const;
};

// ---- Вспомогательные IO-структуры (как в T2) ----

struct DelimiterIO
{
  char exp;
};

struct PointIO
{
  Point& ref;
};

// ---- Перегрузки оператора>> ----
std::istream& operator>>(std::istream& in, DelimiterIO&& dest);
std::istream& operator>>(std::istream& in, PointIO&& dest);
std::istream& operator>>(std::istream& in, Polygon& dest);

// ---- Перегрузки оператора<< ----
std::ostream& operator<<(std::ostream& out, const Point& src);
std::ostream& operator<<(std::ostream& out, const Polygon& src);

// ---- Геометрические вычисления ----

// Площадь по формуле Гаусса (шнурок)
double getArea(const Polygon& p);

// Пересекаются ли два выпуклых полигона (теорема разделяющей оси SAT)
bool intersects(const Polygon& a, const Polygon& b);

// Функторы для использования с алгоритмами STL

struct AreaAccumulator
{
  double operator()(double acc, const Polygon& p) const;
};

struct EvenVertexPred
{
  bool operator()(const Polygon& p) const;
};

struct OddVertexPred
{
  bool operator()(const Polygon& p) const;
};

struct VertexCountPred
{
  explicit VertexCountPred(std::size_t n);
  bool operator()(const Polygon& p) const;
  std::size_t count;
};

struct AreaLess
{
  bool operator()(const Polygon& a, const Polygon& b) const;
};

struct VertexCountLess
{
  bool operator()(const Polygon& a, const Polygon& b) const;
};

struct AreaLessThan
{
  explicit AreaLessThan(double threshold);
  bool operator()(const Polygon& p) const;
  double threshold;
};

struct IntersectsWith
{
  explicit IntersectsWith(const Polygon& target);
  bool operator()(const Polygon& p) const;
  const Polygon& target;
};

// Для AREA EVEN/ODD — накапливает площадь только подходящих фигур
struct ConditionalAreaAccumulator
{
  explicit ConditionalAreaAccumulator(bool even);
  double operator()(double acc, const Polygon& p) const;
  bool even; // true = чётные, false = нечётные
};

struct VertexCountAreaAccumulator
{
  explicit VertexCountAreaAccumulator(std::size_t n);
  double operator()(double acc, const Polygon& p) const;
  std::size_t count;
};

#endif // POLYGON_H

