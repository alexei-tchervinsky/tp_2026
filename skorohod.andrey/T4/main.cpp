#include <iostream>
#include <iomanip>
#include <vector>
#include <memory>
#include "rectangle.hpp"
#include "circle.hpp"
#include "compositeShape.hpp"

int main()
{
    std::vector<Shape*> shapeContainer;
    Point p1{0,3}, p2{4,4}, p3{5,4};
    Rectangle rect1({1,2}, {4,5});
    Rectangle rect2(p1, p2);
    Circle circle1({3,3}, 3);
    Circle circle2(p3, 5);

    Rectangle rect3({2,2}, {4,4});
    Circle circle3({0,2}, 4);
    CompositeShape composite;
    composite.addShape(rect3);
    composite.addShape(circle3);

    shapeContainer.push_back(&rect1);
    shapeContainer.push_back(&rect2);
    shapeContainer.push_back(&circle1);
    shapeContainer.push_back(&circle2);
    shapeContainer.push_back(&composite);

    std::cout << std::fixed << std::setprecision(2);
    for (auto i : shapeContainer)
    {
        std::cout << *i << '\n';
    }

    for (auto i : shapeContainer)
    {
        i->scale(2);
    }

    for (auto i : shapeContainer)
    {
        std::cout << *i << '\n';
    }
    return 0;
}
