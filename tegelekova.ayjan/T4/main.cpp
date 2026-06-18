#include <iostream>
#include <iomanip>
#include <memory>
#include <vector>
#include "point.h"
#include "rectangle.h"
#include "circle.h"
#include "composite_shape.h"

void printShape(const Shape& shape) {
    std::cout << std::fixed << std::setprecision(2);
    Point center = shape.getCenter();

    std::cout << "[" << shape.getName()
              << ", (" << center.x << ", " << center.y << "), "
              << shape.getArea() << "]";
}

void printComposite(const CompositeShape& composite) {
    std::cout << std::fixed << std::setprecision(2);
    Point center = composite.getCenter();

    std::cout << "[COMPOSITE, (" << center.x << ", " << center.y << "), "
              << composite.getArea() << ":\n";

    const auto& shapes = composite.getShapes();
    for (size_t i = 0; i < shapes.size(); ++i) {
        std::cout << "    ";
        printShape(*shapes[i]);
        if (i < shapes.size() - 1) std::cout << ",";
        std::cout << "\n";
    }
    std::cout << "]";
}

int main() {
    std::vector<std::unique_ptr<Shape>> shapes;

    // 1. Прямоугольник
    shapes.push_back(std::make_unique<Rectangle>(Point(0, 0), Point(4, 3)));

    // 2. Круг
    shapes.push_back(std::make_unique<Circle>(Point(5, 5), 2));

    // 3. Ещё один прямоугольник
    shapes.push_back(std::make_unique<Rectangle>(Point(-2, -1), Point(1, 2)));

    // 4. Составная фигура
    auto composite = std::make_unique<CompositeShape>();
    composite->addShape(std::make_unique<Rectangle>(Point(0, 0), Point(2, 2)));
    composite->addShape(std::make_unique<Circle>(Point(3, 3), 1));
    composite->addShape(std::make_unique<Rectangle>(Point(4, 0), Point(6, 1)));
    shapes.push_back(std::move(composite));

    // 5. Ещё один круг
    shapes.push_back(std::make_unique<Circle>(Point(-3, -2), 1.5));

    std::cout << "========== ДО МАСШТАБИРОВАНИЯ ==========\n\n";
    for (const auto& shape : shapes) {
        if (shape->getName() == "COMPOSITE") {
            printComposite(dynamic_cast<const CompositeShape&>(*shape));
        } else {
            printShape(*shape);
        }
        std::cout << "\n\n";
    }

    // Масштабируем всё в 2 раза
    for (auto& shape : shapes) {
        shape->scale(2.0);
    }

    std::cout << "\n========== ПОСЛЕ МАСШТАБИРОВАНИЯ (x2) ==========\n\n";
    for (const auto& shape : shapes) {
        if (shape->getName() == "COMPOSITE") {
            printComposite(dynamic_cast<const CompositeShape&>(*shape));
        } else {
            printShape(*shape);
        }
        std::cout << "\n\n";
    }

    return 0;
}
