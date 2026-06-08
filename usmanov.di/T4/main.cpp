#include <iostream>
#include <iomanip>
#include <vector>
#include <memory>
#include "Circle.h"
#include "Rectangle.h"
#include "CompositeShape.h"

int main() {
    std::vector<std::unique_ptr<Shape>> shapes;

    shapes.push_back(std::make_unique<Circle>(0.0, 0.0, 5.0));
    shapes.push_back(std::make_unique<Circle>(10.0, 10.0, 3.0));
    shapes.push_back(std::make_unique<Rectangle>(0.0, 0.0, 10.0, 10.0));
    shapes.push_back(std::make_unique<Rectangle>(5.0, 5.0, 15.0, 15.0));

    Circle c1(2.0, 2.0, 2.0);
    Circle c2(8.0, 8.0, 1.5);
    Rectangle r1(3.0, 3.0, 7.0, 7.0);
    shapes.push_back(std::make_unique<CompositeShape>(c1, c2, r1));

    std::cout << "Initial Shapes\n";
    for (const auto& shape : shapes) {
        std::cout << "[" << *shape << "]\n\n";
    }

    for (auto& shape : shapes) {
        shape->scale(2.0);
    }

    std::cout << "\nAfter Scale(2)\n";
    for (const auto& shape : shapes) {
        std::cout << "[" << *shape << "]\n\n";
    }

    return 0;
}
