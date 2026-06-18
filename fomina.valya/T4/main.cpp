#include <iomanip>
#include <iostream>

#include "composite_shape.h"
#include "point.h"
#include "rectangle.h"
#include "square.h"

// #include <iostream>
// #include <vector>
// #include <memory>
int main() {
    std::cout << "========= RECANGLE =========\n\n";
    std::cout << std::fixed << std::setprecision(2);
    {
        Rectangle rect({0, 0}, {10, 10});

        std::cout << "rect: {0,0}, {10,10}";

        std::cout << "\nchecking methods...\n";

        std::cout << "\ngetArea(): " << rect.getArea() << "\n";
        Point p = rect.getCenter();
        std::cout << "Center: " << "(" << p.x_ << "; " << p.y_ << ")\n";
        rect.move(5, 5);
        Point p2 = rect.getCenter();
        std::cout << "Moved dx = 5, dy = 5: " << "(" << p2.x_ << "; " << p2.y_ << ")\n";
        rect.scale(4);
        std::cout << "scale(4) :" << rect.getArea() << "\n";
        std::cout << "getName():" << rect.getName() << "\n";
    }

    std::cout << "\n\n========= SQUARE =========\n\n";
    {
        Square sqr({0, 0}, 5);

        std::cout << "Square ( {0,0} 5)";

        std::cout << "\nchecking methods...\n";

        std::cout << "\ngetArea(): " << sqr.getArea() << "\n";
        Point p = sqr.getCenter();
        std::cout << "Center: " << "(" << p.x_ << "; " << p.y_ << ")\n";
        sqr.move(5, 5);
        Point p2 = sqr.getCenter();
        std::cout << "Moved dx = 5, dy = 5: " << "(" << p2.x_ << "; " << p2.y_ << ")\n";
        sqr.scale(4);
        std::cout << "scale(4) :" << sqr.getArea() << "\n";
        std::cout << "getName():" << sqr.getName() << "\n";
    }

    std::cout << "\n\n=======COMPOSITE SHAPE=======\n\n";
    {
        std::unique_ptr<Rectangle> rect = std::make_unique<Rectangle>(Point{0, 0}, Point{4, 4});

        CompositeShape composite;
        composite.addShape(std::move(rect));

        std::cout << "Center: (" << composite.getCenter().x_ << ", " << composite.getCenter().y_ << ")\n";
        std::cout << "Area: " << composite.getArea() << '\n';

        composite.scale(2.0);

        std::cout << "\nafter scale (x4):\n";
        std::cout << "Center: (" << composite.getCenter().x_ << ", " << composite.getCenter().y_ << ")\n";
        std::cout << "Area: " << composite.getArea() << '\n';
    }
}
