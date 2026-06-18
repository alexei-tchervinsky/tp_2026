#include <iomanip>
#include <iostream>
#include <memory>
#include <vector>

#include "circle.hpp"
#include "shape.hpp"
#include "square.hpp"

namespace
{
void printShape(const Shape & shape)
{
  const Point center = shape.getCenter();

  std::cout << '[' << shape.getName() << ", ("
            << std::fixed << std::setprecision(2)
            << center.x << ", " << center.y << "), "
            << shape.getArea() << "]\n";
}
}

int main()
{
  std::vector< std::unique_ptr< Shape > > shapes;
  shapes.push_back(std::make_unique< Circle >(Point{0.0, 0.0}, 2.0));
  shapes.push_back(std::make_unique< Circle >(Point{3.0, -1.0}, 1.5));
  shapes.push_back(std::make_unique< Square >(Point{1.0, 1.0}, 4.0));
  shapes.push_back(std::make_unique< Square >(Point{-3.0, 2.0}, 2.0));
  shapes.push_back(std::make_unique< Circle >(Point{5.0, 5.0}, 3.0));

  std::cout << "Before scaling:\n";
  for (const std::unique_ptr< Shape > & shape: shapes)
  {
    printShape(*shape);
  }

  for (std::unique_ptr< Shape > & shape: shapes)
  {
    shape->scale(2.0);
  }

  std::cout << "\nAfter scaling:\n";
  for (const std::unique_ptr< Shape > & shape: shapes)
  {
    printShape(*shape);
  }

  return 0;
}
