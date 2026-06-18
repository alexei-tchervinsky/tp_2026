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

  try {
    // Тест 1 Квадрат
    Shape *square = new Square(Point(1, 1), 2);
    shapes.push_back(square);
    std::cout << "=== Test 1: Square ===" << std::endl;
    printInfo(*square);
    square->move(Point(4, 4));
    printInfo(*square);
    square->move(-1, -1);
    printInfo(*square);
    square->scale(1.5);
    printInfo(*square);

    // Тест 2: Круг
    Shape *circle = new Circle(Point(3, 3), 1.5);
    shapes.push_back(circle);
    std::cout << "\n=== Test 2: Circle ===" << std::endl;
    printInfo(*circle);
    circle->move(Point(5, 1));
    printInfo(*circle);
    circle->move(0, 1);
    printInfo(*circle);
    circle->scale(0.8);
    printInfo(*circle);

    // Тест 3: Составная фигура
    // Используем new, чтобы избежать Segmentation Fault при удалении из вектора
    CompositeShape *composite = new CompositeShape(2);
    composite->addShape(square->clone());
    composite->addShape(circle->clone());
    shapes.push_back(composite);

    std::cout << "\n=== Test 3: Composite Shape ===" << std::endl;
    printInfo(*composite);
    composite->move(Point(6, 6));
    printInfo(*composite);
    composite->move(Point(-1, -1));
    printInfo(*composite);
    composite->scale(2.0);
    printInfo(*composite);

    // Масштабирование всего вектора
    std::cout << "\nAfter final global scaling:" << std::endl;
    for (auto shape : shapes) {
      shape->scale(1.5);
      printInfo(*shape);
    }

  } catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << std::endl;
  }

  // Безопасная очистка всей памяти
  for (auto shape : shapes) {
    delete shape;
  }

  return 0;
}
