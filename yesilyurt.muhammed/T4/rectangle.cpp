#include "rectangle.h"
#include <stdexcept>

Rectangle::Rectangle(const Point& lb, const Point& rt) : leftBottom(lb), rightTop(rt)
{
    if (lb.x >= rt.x || lb.y >= rt.y)
    {
        throw std::invalid_argument("Invalid rectangle points");
    }
}

double Rectangle::getArea() const
{
    return (rightTop.x - leftBottom.x) * (rightTop.y - leftBottom.y);
}

Point Rectangle::getCenter() const
{
    return Point{(leftBottom.x + rightTop.x) / 2.0, (leftBottom.y + rightTop.y) / 2.0};
}

void Rectangle::move(double dx, double dy)
{
    leftBottom.x += dx;
    leftBottom.y += dy;
    rightTop.x += dx;
    rightTop.y += dy;
}

void Rectangle::scale(double factor)
{
    if (factor <= 0)
    {
        throw std::invalid_argument("Scale factor must be positive");
    }

    Point center = getCenter();
    double halfWidth = (rightTop.x - leftBottom.x) / 2.0;
    double halfHeight = (rightTop.y - leftBottom.y) / 2.0;

    halfWidth *= factor;
    halfHeight *= factor;

    leftBottom = Point{center.x - halfWidth, center.y - halfHeight};
    rightTop = Point{center.x + halfWidth, center.y + halfHeight};
}

std::string Rectangle::getName() const
{
    return "RECTANGLE";
}

double Rectangle::getLeft() const
{
    return leftBottom.x;
}

double Rectangle::getRight() const
{
    return rightTop.x;
}

double Rectangle::getBottom() const
{
    return leftBottom.y;
}

double Rectangle::getTop() const
{
    return rightTop.y;
}
