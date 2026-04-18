#include <iostream>
#include "rectangle.hpp"
#include "ellipse.hpp"
#include "composite_shape.hpp"
#include <vector>
#include <memory>
#include <iomanip>

void printShapeInfo(const std::shared_ptr<Shape>& shape) {
    Point center = shape->getCenter();
    std::cout << "[" << shape->getName() << ", ("
              << std::fixed << std::setprecision(2)
              << center.x_ << ", " << center.y_ << "), "
              << shape->getArea() << "]" << "\n";
}

int main() {
    std::vector<std::shared_ptr<Shape>> shapes;

    auto rect1 = std::make_shared<Rectangle>(Point{0.0, 0.0}, Point{2.0, 2.0});
    auto rect2 = std::make_shared<Rectangle>(Point{5.0, 5.0}, Point{10.0, 7.0});
    auto ell1 = std::make_shared<Ellipse>(Point{0.0, 0.0}, 5.0, 3.0);
    auto ell2 = std::make_shared<Ellipse>(Point{-5.0, -5.0}, 2.0, 2.0);

    auto composite = std::make_shared<CompositeShape>();
    composite->add(rect1);
    composite->add(ell1);

    shapes.push_back(rect1);
    shapes.push_back(rect2);
    shapes.push_back(ell1);
    shapes.push_back(ell2);
    shapes.push_back(composite);

    std::cout << "BEFORE============================\n";
    for (const auto& sh : shapes) {
        printShapeInfo(sh);
    }

    std::cout << "============================\n";
    for (const auto& sh : shapes) {
        sh->scale(2.0);
    }

    std::cout << "\nAFTER===================================\n";
    for (const auto& sh : shapes) {
        printShapeInfo(sh);
    }
    return 0;
}
