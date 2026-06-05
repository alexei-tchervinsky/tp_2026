#include <iostream>
#include <memory>
#include "rectangle.hpp"
#include "circle.hpp"
#include "compositeshape.hpp"
int main()
{
  Point lb;
  lb.x = 0;
  lb.y = 0;
  Point rt;
  rt.x = 4;
  rt.y = 2;
  auto rect = std::make_shared<Rectangle>(lb, rt);
  Point center;
  center.x = 5;
  center.y = 5;
  auto circ = std::make_shared<Circle>(center, 3);
  CompositeShape comp;
  comp.addShape(rect);
  comp.addShape(circ);
  std::cout << comp.getName() << '\n';
  std::cout << comp.getArea() << '\n';
  Point compCenter = comp.getCenter();
  std::cout << compCenter.x << " "
            << compCenter.y << '\n';
  comp.scale(3);
  std::cout << comp.getArea() << '\n';
  return 0;
}
