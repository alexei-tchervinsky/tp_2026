#include <iostream>
#include <iomanip>
#include <memory>
#include "rectangle.hpp"
#include "circle.hpp"
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
                std::cout << "  " << s->getName() << ", (" << sc.x << ", " << sc.y << "), " << s->getArea() << "\n";
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

    // Создаём 2 прямоугольника
    Rectangle rect1({0.0, 0.0}, {2.0, 3.0});   // площадь 6
    Rectangle rect2({1.0, 1.0}, {4.0, 5.0});   // площадь 9

    // Создаём 2 круга
    Circle circle1({0.0, 0.0}, 2.0);   // площадь ~12.57
    Circle circle2({3.0, 3.0}, 1.0);   // площадь ~3.14

    // Создаём составную фигуру (внутри: прямоугольник + круг)
    CompositeShape composite;
    composite.addShape(std::make_unique<Rectangle>(Point{0.0, 0.0}, Point{1.0, 1.0}));
    composite.addShape(std::make_unique<Circle>(Point{2.0, 2.0}, 1.0));

    std::cout << "Before scaling (factor = 2):\n";
    printShape(rect1);
    printShape(rect2);
    printShape(circle1);
    printShape(circle2);
    printShape(composite);

    // Масштабируем всё в 2 раза
    rect1.scale(2.0);
    rect2.scale(2.0);
    circle1.scale(2.0);
    circle2.scale(2.0);
    composite.scale(2.0);

    std::cout << "\nAfter scaling (factor = 2):\n";
    printShape(rect1);
    printShape(rect2);
    printShape(circle1);
    printShape(circle2);
    printShape(composite);

    return 0;
}
