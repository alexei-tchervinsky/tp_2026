#include <iostream>
#include <iomanip>
#include "rectangle.hpp"
#include "ring.hpp"
#include "composite-shape.hpp"

void printShape(const Shape* shape) {
    if (shape == nullptr) return;
    Point c = shape->getCenter();
    std::cout << "[" << shape->getName() << ", ("
        << std::fixed << std::setprecision(2)
        << c.x_ << ", " << c.y_ << "), "
        << shape->getArea() << "]\n";
}

int main() {
    try {
        Shape* shapes[5];

        // 1. Прямоугольник
        shapes[0] = new Rectangle(1.0, 1.0, 2.0, 2.0);

        // 2. Кольцо (Ring)
        shapes[1] = new Ring(5.0, 5.0, 2.0, 4.0);

        // 3. Еще один прямоугольник
        shapes[2] = new Rectangle(-2.0, 0.0, 1.0, 3.0);

        // 4. Еще одно кольцо
        shapes[3] = new Ring(10.0, -2.0, 1.0, 2.0);

        CompositeShape* cs = new CompositeShape(2);
        cs->addShape(new Rectangle(0.0, 0.0, 2.0, 2.0));
        cs->addShape(new Ring(0.0, 0.0, 1.0, 3.0));
        shapes[4] = cs;

        std::cout << "Before scaling:\n";
        for (std::size_t i = 0; i < 5; ++i) {
            printShape(shapes[i]);
        }

        for (std::size_t i = 0; i < 5; ++i) {
            shapes[i]->scale(2.0);
        }

        std::cout << "\nAfter scaling (x2.0):\n";
        for (std::size_t i = 0; i < 5; ++i) {
            printShape(shapes[i]);
        }
        for (std::size_t i = 0; i < 5; ++i) {
            delete shapes[i];
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
