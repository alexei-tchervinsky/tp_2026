#include <iostream>
#include <iomanip>
#include <memory>
#include "rectangle.hpp"
#include "circle.hpp"
#include "ring.hpp"
#include "ellipse.hpp"
#include "composite_shape.hpp"

namespace golovach {
  void printShape(const Shape& shape) {
    if (shape.getName() == std::string("COMPOSITE")) {
      const CompositeShape& cs = static_cast<const CompositeShape&>(shape);
      Point c = cs.getCenter();
      std::cout << std::fixed << std::setprecision(2);
      std::cout << "[COMPOSITE, (" << c.x << ", " << c.y << "), " << cs.getArea() << ":\n";
      for (const auto& s : cs.getShapes()) {
        Point sc = s->getCenter();
        std::cout << " " << s->getName() << ", (" << sc.x << ", " << sc.y << "), " << s->getArea() << ",\n";
      }
      std::cout << "]\n";
    } else {
      Point c = shape.getCenter();
      std::cout << std::fixed << std::setprecision(2);
      std::cout << "[" << shape.getName() << ", (" << c.x << ", " << c.y << "), " << shape.getArea() << "]\n";
    }
  }
}

int main() {
  using namespace golovach;

  Rectangle rect({1.0, 1.0}, {3.0, 4.0});
  Circle circle({0.0, 0.0}, 5.0);
  Ring ring({2.0, 2.0}, 4.0, 2.0);
  Ellipse ellipse({0.0, 0.0}, 3.0, 6.0);

  CompositeShape composite;
  composite.addShape(std::make_unique<Rectangle>(Point{0.0, 0.0}, Point{2.0, 2.0}));
  composite.addShape(std::make_unique<Circle>(Point{1.0, 1.0}, 1.0));

  std::cout << "Before scaling:\n";
  printShape(rect);
  printShape(circle);
  printShape(ring);
  printShape(ellipse);
  printShape(composite);

  rect.scale(2.0);
  circle.scale(2.0);
  ring.scale(2.0);
  ellipse.scale(2.0);
  composite.scale(2.0);

  std::cout << "\nAfter scaling:\n";
  printShape(rect);
  printShape(circle);
  printShape(ring);
  printShape(ellipse);
  printShape(composite);

  return 0;
}
