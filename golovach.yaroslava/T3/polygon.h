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

// ---- Вспомогательные IO-структуры ----

struct DelimiterIO
{
  char exp;
};

struct PointIO
{
  Point& ref;
};

// ---- Перегрузки операторов ввода/вывода ----
std::istream& operator>>(std::istream& in, DelimiterIO&& dest);
std::istream& operator>>(std::istream& in, PointIO&& dest);
std::istream& operator>>(std::istream& in, Polygon& dest);

std::ostream& operator<<(std::ostream& out, const Point& src);
std::ostream& operator<<(std::ostream& out, const Polygon& src);

// ---- Геометрические вычисления ----
double getArea(const Polygon& p);
bool intersects(const Polygon& a, const Polygon& b);

// ---- Функторы для обязательных команд ----
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

struct ConditionalAreaAccumulator
{
  explicit ConditionalAreaAccumulator(bool even);
  double operator()(double acc, const Polygon& p) const;
  bool even;
};

struct VertexCountAreaAccumulator
{
  explicit VertexCountAreaAccumulator(std::size_t n);
  double operator()(double acc, const Polygon& p) const;
  std::size_t count;
};


// Проверка совместимости наложением (параллельный перенос, без поворота)
bool isSameShape(const Polygon& a, const Polygon& b);

// Функтор для SAME
struct SamePred
{
  const Polygon& target;
  explicit SamePred(const Polygon& t);
  bool operator()(const Polygon& p) const;
};

#endif // POLYGON_H
