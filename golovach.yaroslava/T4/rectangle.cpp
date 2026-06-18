#include "rectangle.hpp"

namespace golovach {
    Rectangle::Rectangle(Point bottomLeft, Point topRight)
        : bottomLeft_(bottomLeft), topRight_(topRight) {}

    double Rectangle::getArea() const {
        return (topRight_.x - bottomLeft_.x) * (topRight_.y - bottomLeft_.y);
    }

    Point Rectangle::getCenter() const {
        return { (bottomLeft_.x + topRight_.x) / 2.0,
                 (bottomLeft_.y + topRight_.y) / 2.0 };
    }

    void Rectangle::move(double dx, double dy) {
        bottomLeft_.x += dx;
        bottomLeft_.y += dy;
        topRight_.x += dx;
        topRight_.y += dy;
    }

    void Rectangle::scale(double factor) {
        Point center = getCenter();
        bottomLeft_.x = center.x + (bottomLeft_.x - center.x) * factor;
        bottomLeft_.y = center.y + (bottomLeft_.y - center.y) * factor;
        topRight_.x   = center.x + (topRight_.x   - center.x) * factor;
        topRight_.y   = center.y + (topRight_.y   - center.y) * factor;
    }

    const char* Rectangle::getName() const {
        return "RECTANGLE";
    }
}
