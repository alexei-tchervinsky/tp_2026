#include <iostream>
#include <iomanip>
#include <vector>
#include <memory>
#include "rectangle.h"
#include "circle.h"
#include "composite_shape.h"

int main() {
    std::vector<std::unique_ptr<Shape>> shapes;

    shapes.push_back(std::make_unique<Rectangle>(Point{ 0, 0 }, Point{ 4, 3 }));
    shapes.push_back(std::make_unique<Circle>(Point{ 5, 5 }, 2));
    shapes.push_back(std::make_unique<Rectangle>(Point{ -2, -2 }, Point{ 2, 2 }));

    auto composite = std::make_unique<CompositeShape>();
    composite->addShape(std::make_unique<Circle>(Point{ 10, 10 }, 1.5));
    composite->addShape(std::make_unique<Rectangle>(Point{ 8, 8 }, Point{ 12, 12 }));
    shapes.push_back(std::move(composite));

    shapes.push_back(std::make_unique<Circle>(Point{ -5, 0 }, 1));

    std::cout << std::fixed << std::setprecision(2);

    for (const auto& s : shapes) {
        Point c = s->getCenter();
        std::cout << "[" << s->getName() << ", (" << c.x << ", " << c.y << "), " << s->getArea() << "]\n";
    }

    for (auto& s : shapes) {
        s->scale(2);
    }

    std::cout << "\n";

    for (const auto& s : shapes) {
        Point c = s->getCenter();
        std::cout << "[" << s->getName() << ", (" << c.x << ", " << c.y << "), " << s->getArea() << "]\n";
    }

    return 0;
}
