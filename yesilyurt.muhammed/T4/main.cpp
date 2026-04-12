#include <iostream>
#include <vector>
#include <memory>
#include <iomanip>

#include "rectangle.h"
#include "circle.h"
#include "compositeshape.h"

void printShape(const Shape& shape)
{
    Point center = shape.getCenter();

    std::cout << "[" << shape.getName()
              << ", (" << std::fixed << std::setprecision(2)
              << center.x << ", " << center.y << "), "
              << shape.getArea() << "]";
}

void printComposite(const CompositeShape& composite)
{
    Point center = composite.getCenter();

    std::cout << "[" << composite.getName()
              << ", (" << std::fixed << std::setprecision(2)
              << center.x << ", " << center.y << "), "
              << composite.getArea() << ":\n";

    for (const auto& shape : composite.getShapes())
    {
        Point c = shape->getCenter();
        std::cout << " " << shape->getName()
                  << ", (" << c.x << ", " << c.y << "), "
                  << shape->getArea() << "\n";
    }

    std::cout << "]\n";
}

int main()
{
    try
    {
        std::vector<std::unique_ptr<Shape>> shapes;

        shapes.push_back(std::make_unique<Rectangle>(Point{0.0, 0.0}, Point{4.0, 3.0}));
        shapes.push_back(std::make_unique<Rectangle>(Point{1.0, 1.0}, Point{5.0, 4.0}));
        shapes.push_back(std::make_unique<Circle>(Point{2.0, 2.0}, 1.0));
        shapes.push_back(std::make_unique<Circle>(Point{6.0, 1.0}, 2.0));

        auto composite = std::make_unique<CompositeShape>();
        composite->addShape(std::make_unique<Rectangle>(Point{0.0, 0.0}, Point{2.0, 2.0}));
        composite->addShape(std::make_unique<Circle>(Point{4.0, 4.0}, 1.5));

        shapes.push_back(std::move(composite));

        std::cout << "Before scaling:\n";
        for (const auto& shape : shapes)
        {
            if (shape->getName() == "COMPOSITE")
            {
                printComposite(dynamic_cast<const CompositeShape&>(*shape));
            }
            else
            {
                printShape(*shape);
                std::cout << "\n";
            }
        }

        for (auto& shape : shapes)
        {
            shape->scale(2.0);
        }

        std::cout << "\nAfter scaling by 2:\n";
        for (const auto& shape : shapes)
        {
            if (shape->getName() == "COMPOSITE")
            {
                printComposite(dynamic_cast<const CompositeShape&>(*shape));
            }
            else
            {
                printShape(*shape);
                std::cout << "\n";
            }
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << "\n";
    }

    return 0;
}
