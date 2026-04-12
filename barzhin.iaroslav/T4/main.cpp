#include <iostream>
#include <memory>
#include <cmath>
#include <stdexcept>
#include <string>
#include "rectangle.h"
#include "circle.h"
#include "composite_shape.h"

void expect(bool condition, const std::string& message) {
    if (!condition) {
        throw std::runtime_error("Test Failed: " + message);
    }
}

bool isClose(double a, double b, double tolerance = 0.01) {
    return std::abs(a - b) < tolerance;
}

void runTests() {
    {
        Rectangle rect({0, 0}, {10, 10});
        expect(isClose(rect.getArea(), 100.0), "Rectangle Area");
        expect(isClose(rect.getCenter().x, 5.0), "Rectangle Center X");
    }

    {
        CompositeShape cs;
        cs.addShape(std::make_unique<Rectangle>(Point{0, 0}, Point{10, 10}));
        cs.addShape(std::make_unique<Rectangle>(Point{20, 0}, Point{30, 10}));

        double oldArea = cs.getArea();
        Point oldCenter = cs.getCenter();

        cs.scale(2.0);

        expect(isClose(cs.getArea(), oldArea * 4.0), "Composite Area Scale x4");
        expect(isClose(cs.getCenter().x, oldCenter.x), "Composite Center Invariance");

        expect(isClose(cs.getLeftLow().x, -15.0), "Composite Shifting Logic (Left)");
        expect(isClose(cs.getRightTop().x, 45.0), "Composite Shifting Logic (Right)");
    }
}

int main() {
    try {
        std::cout << "Running validation tests..." << std::endl;
        runTests();
        std::cout << "All internal tests passed!" << std::endl;

        CompositeShape group;
        group.addShape(std::make_unique<Rectangle>(Point{0,0}, Point{2,2}));
        group.addShape(std::make_unique<Circle>(Point{5,5}, 1.0));
        group.addShape(std::make_unique<Rectangle>(Point{10,10}, Point{12,12}));
        group.addShape(std::make_unique<Circle>(Point{-5,-5}, 2.0));

        auto subGroup = std::make_unique<CompositeShape>();
        subGroup->addShape(std::make_unique<Rectangle>(Point{0,0}, Point{1,1}));
        group.addShape(std::move(subGroup));

        std::cout << "--- BEFORE SCALE ---" << std::endl;
        group.print();

        group.scale(2.0);

        std::cout << "\n--- AFTER SCALE (x2) ---" << std::endl;
        group.print();

    } catch (const std::exception& e) {
        std::cerr << "CRITICAL ERROR: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
