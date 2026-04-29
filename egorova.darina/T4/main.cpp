#include "shapes.hpp"
#include <iomanip>
#include <iostream>
#include <vector>

void printInfo(const Shape &shape) {
  FrameRectangle frame = shape.getFrame();
  Point bl = frame.getBottomLeft();
  Point tr = frame.getTopRight();
  std::cout << std::fixed << std::setprecision(2);
  std::cout << shape.getName() << " " << shape.area() << " " << bl.x << " "
            << bl.y << " " << tr.x << " " << tr.y << std::endl;
}

int main() {
  std::vector<Shape *> shapes;
  bool scaleCompleted = false;

  try {
    // Создание Квадрата
    double x = 1, y = 1, side = 2;
    Shape *square = new Square(Point(x, y), side);
    shapes.push_back(square);

    // Создание Круга
    double circleX = 3, circleY = 3, radius = 1.5;
    Shape *circle = new Circle(Point(circleX, circleY), radius);
    shapes.push_back(circle);

    // Создание составной фигуры (CompositeShape)
    CompositeShape composite(2);
    composite.addShape(square->clone());
    composite.addShape(circle->clone());
    shapes.push_back(&composite);

    std::cout << "=== Test 1: Square ===" << std::endl;
    printInfo(*square);
    square->move(Point(4, 4));
    printInfo(*square);
    square->move(-1, -1);
    printInfo(*square);
    square->scale(1.5);
    printInfo(*square);

    std::cout << "\n=== Test 2: Circle ===" << std::endl;
    printInfo(*circle);
    circle->move(Point(5, 1));
    printInfo(*circle);
    circle->move(0, 1);
    printInfo(*circle);
    circle->scale(0.8);
    printInfo(*circle);

    std::cout << "\n=== Test 3: Composite Shape ===" << std::endl;
    printInfo(composite);
    composite.move(Point(6, 6));
    printInfo(composite);
    composite.move(-1, -1);
    printInfo(composite);
    composite.scale(2);
    printInfo(composite);

    // Масштабирование всех фигур
    double scaleFactor = 1.5;
    for (auto shape : shapes) {
      shape->scale(scaleFactor);
    }
    scaleCompleted = true;

    std::cout << "\nAfter scaling all shapes:" << std::endl;
    for (auto shape : shapes) {
      printInfo(*shape);
    }

  } catch (const std::exception &e) {
    std::cerr << e.what() << std::endl;
    if (!scaleCompleted) {
      std::cerr << "Scale wasn't completed" << std::endl;
    }
  }

  for (auto shape : shapes) {
    if (shape && shape->getName() != "COMPOSITE_SHAPE") {
      delete shape;
    }
  }
  return 0;
}
