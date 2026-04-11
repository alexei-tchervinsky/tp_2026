#include <iostream>
#include <iomanip>
#include <vector>
#include <memory>

#include "rectangle.h"
#include "rhomb.h"
#include "composite_shape.h"

int main() {

    std::cout << "========= RHOMB =========\n\n";
    std::cout << std::fixed << std::setprecision(2);

    std::unique_ptr<Rhombus> rhomb = std::make_unique<Rhombus>(Point{10, 10}, 3.0, 2.0);

    std::cout << "center: 10; 10\nhHalf = 3.0\nvHalf = 2.0\n";

    std::cout << "\nchecking methods...\n";

    std::cout << "\ngetArea():" << rhomb->getArea() << "\n";
    Point p = rhomb->getCenter();
    std::cout << "Center: " << "(" << p.x << "; " << p.y << ")\n";
    rhomb->move(5, 5);
    Point p2 = rhomb->getCenter();
    std::cout << "Moved dx = 5, dy = 5: " << "(" << p2.x << "; " << p2.y << ")\n";
    rhomb->scale(4);
    std::cout << "scale(4) :" << rhomb->getArea() << "\n";
    std::cout << "getName():" << rhomb->getName() << "\n";




    std::unique_ptr<Rectangle> rect = std::make_unique<Rectangle>(Point{0, 0}, Point{4, 4});


    CompositeShape composite;
    composite.addShape(std::move(rect));
    composite.addShape(std::move(rhomb));

    std::cout << "\n ======= composite ======= \n" << std::endl;

    std::cout << "Center: (" << composite.getCenter().x << ", " << composite.getCenter().y << ")" << std::endl;
    std::cout << "Area: " << composite.getArea() << std::endl;

    composite.scale(2.0);

    std::cout << "\nafter scale (x2):" << std::endl;
    std::cout << "Center: (" << composite.getCenter().x << ", " << composite.getCenter().y << ")" << std::endl;
    std::cout << "Area: " << composite.getArea() << std::endl;

    return 0;
}
