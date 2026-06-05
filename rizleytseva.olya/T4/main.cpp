#include <iostream>
#include <iomanip>
#include <memory>
#include <vector>
#include "rectangle.h"
#include "circle.h"
#include "composite_shape.h"

void printShapeInfo(const Shape& s) {
    std::cout << s.getName() << ", ("
              << s.getCenter().x << ", " << s.getCenter().y << "), "
              << s.getArea();
}

void printShape(const Shape& s) {
    std::cout << "[";
    printShapeInfo(s);
    std::cout << "]";
}

void printComposite(const CompositeShape& cs) {
    std::cout << "[" << cs.getName() << ", ("
              << cs.getCenter().x << ", " << cs.getCenter().y << "), "
              << cs.getArea() << ":" << std::endl;

    for (const auto& shape : cs.getShapes()) {
        std::cout << "  ";
        printShapeInfo(*shape);
        std::cout << "," << std::endl;
    }
    std::cout << "]";
}

int main() {
    std::vector<std::unique_ptr<Shape>> shapes;

    shapes.push_back(std::make_unique<Rectangle>(Point(0, 0), Point(4, 3)));
    shapes.push_back(std::make_unique<Circle>(Point(5, 5), 2.0));

    auto composite = std::make_unique<CompositeShape>();
    composite->addShape(std::make_unique<Rectangle>(Point(10, 10), Point(12, 14)));
    composite->addShape(std::make_unique<Circle>(Point(15, 12), 1.5));
    shapes.push_back(std::move(composite));

    shapes.push_back(std::make_unique<Rectangle>(Point(-2, -2), Point(0, 0)));
    shapes.push_back(std::make_unique<Circle>(Point(3, -3), 1.0));

    std::cout << std::fixed << std::setprecision(2);

    std::cout << "=== ДО МАСШТАБИРОВАНИЯ (x2) ===\n";
    for (const auto& shape : shapes) {
        if (shape->getName() == "COMPOSITE") {
            printComposite(static_cast<CompositeShape&>(*shape));
        } else {
            printShape(*shape);
        }
        std::cout << "\n";
    }

    for (auto& shape : shapes) {
        shape->scale(2.0);
    }

    std::cout << "\n=== ПОСЛЕ МАСШТАБИРОВАНИЯ (x2) ===\n";
    for (const auto& shape : shapes) {
        if (shape->getName() == "COMPOSITE") {
            printComposite(static_cast<CompositeShape&>(*shape));
        } else {
            printShape(*shape);
        }
        std::cout << "\n";
    }

    return 0;
}
