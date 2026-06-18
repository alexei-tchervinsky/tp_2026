#include <iostream>
#include <vector>
#include <memory>
#include <iomanip>

#include "rectangle.h"
#include "ring.h"
#include "composite_shape.h"

void printShapeInfo(const Shape& shape) {
    std::cout << std::fixed << std::setprecision(2);

    if (shape.getName() == "COMPOSITE") {
        std::cout << "[" << shape.getName() << ", ("
                  << shape.getCenter().x << ", " << shape.getCenter().y << "), "
                  << shape.getArea() << ":\n";

        const auto& composite = static_cast<const CompositeShape&>(shape);
        for (const auto& subShape : composite.getShapes()) {
            std::cout << "  [" << subShape->getName() << ", ("
                      << subShape->getCenter().x << ", " << subShape->getCenter().y << "), "
                      << subShape->getArea() << "]\n";
        }
        std::cout << "]\n";
    } else {
        std::cout << "[" << shape.getName() << ", ("
                  << shape.getCenter().x << ", " << shape.getCenter().y << "), "
                  << shape.getArea() << "]\n";
    }
}

int main() {
    std::vector<std::unique_ptr<Shape>> shapes;

    shapes.push_back(std::make_unique<Rectangle>(Point{0.0, 0.0}, Point{2.0, 3.0}));

    shapes.push_back(std::make_unique<Ring>(Point{5.0, 5.0}, 4.0, 2.0));

    shapes.push_back(std::make_unique<Rectangle>(Point{-2.0, -2.0}, Point{2.0, 2.0}));

    shapes.push_back(std::make_unique<Ring>(Point{-5.0, 5.0}, 3.0, 1.0));

    auto composite = std::make_unique<CompositeShape>();
    composite->addShape(std::make_unique<Rectangle>(Point{1.0, 1.0}, Point{3.0, 4.0}));
    composite->addShape(std::make_unique<Ring>(Point{2.0, 2.0}, 2.0, 0.5));

    shapes.push_back(std::move(composite));

    std::cout << "до масштабирования \n";
    for (const auto& shape : shapes) {
        printShapeInfo(*shape);
        std::cout << "\n";
    }

    for (auto& shape : shapes) {
        shape->scale(2.0);
    }

    std::cout << "после масштабирования (2x) \n";
    for (const auto& shape : shapes) {
        printShapeInfo(*shape);
        std::cout << "\n";
    }

    return 0;
}
