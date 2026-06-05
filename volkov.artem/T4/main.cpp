#include <iostream>
#include <vector>
#include <memory>
#include <iomanip>
#include "rectangle.hpp"
#include "circle.hpp"
#include "compositeshape.hpp"

void printShape(const std::shared_ptr<Shape> &shape) {
    Point center = shape->getCenter();

    if (shape->getName() != "COMPOSITE") {
        std::cout << "[" << shape->getName()
                << ", (" << center.x << ", " << center.y << ")"
                << ", " << shape->getArea() << "]" << std::endl;
    } else {
        std::shared_ptr<CompositeShape> composite = std::dynamic_pointer_cast<CompositeShape>(shape);

        std::cout << "[" << composite->getName()
                << ", (" << center.x << ", " << center.y << ")"
                << ", " << composite->getArea() << ":" << std::endl;

        for (const auto &item: composite->getShapes()) {
            Point c = item->getCenter();
            std::cout << " " << item->getName()
                    << ", (" << c.x << ", " << c.y << ")"
                    << ", " << item->getArea() << "," << std::endl;
        }

        std::cout << "]" << std::endl;
    }
}

int main() {
    std::cout << std::fixed << std::setprecision(2);

    std::vector<std::shared_ptr<Shape> > shapes;

    shapes.push_back(std::make_shared<Rectangle>(Point{0.0, 0.0}, Point{4.0, 2.0}));
    shapes.push_back(std::make_shared<Rectangle>(Point{1.0, 1.0}, Point{3.0, 4.0}));
    shapes.push_back(std::make_shared<Circle>(Point{2.0, 2.0}, 1.0));
    shapes.push_back(std::make_shared<Circle>(Point{5.0, 3.0}, 2.0));

    std::shared_ptr<CompositeShape> composite = std::make_shared<CompositeShape>();
    composite->addShape(std::make_shared<Rectangle>(Point{0.0, 0.0}, Point{2.0, 2.0}));
    composite->addShape(std::make_shared<Circle>(Point{4.0, 4.0}, 1.0));
    shapes.push_back(composite);

    for (const auto &shape: shapes) {
        printShape(shape);
    }

    std::cout << std::endl;

    for (auto &shape: shapes) {
        shape->scale(2.0);
    }

    for (const auto &shape: shapes) {
        printShape(shape);
    }

    return 0;
}
