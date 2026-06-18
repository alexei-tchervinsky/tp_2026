#include "circle.h"
#include <stdexcept>

const double PI = 3.14159265358979323846;

Circle::Circle(const Point& c, double r) : center(c), radius(r)
{
    if (r <= 0)
    {
        throw std::invalid_argument("Radius must be positive");
    }
}

double Circle::getArea() const
{
    return PI * radius * radius;
}

Point Circle::getCenter() const
{
    return center;
}

void Circle::move(double dx, double dy)
{
    center.x += dx;
    center.y += dy;
}

void Circle::scale(double factor)
{
    if (factor <= 0)
    {
        throw std::invalid_argument("Scale factor must be positive");
    }

    radius *= factor;
}

std::string Circle::getName() const
{
    return "CIRCLE";
}

double Circle::getLeft() const
{
    return center.x - radius;
}

double Circle::getRight() const
{
    return center.x + radius;
}

double Circle::getBottom() const
{
    return center.y - radius;
}

double Circle::getTop() const
{
    return center.y + radius;
}
