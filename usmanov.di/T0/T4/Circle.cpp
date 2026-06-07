#include "Circle.h"

double Circle::getArea() const
{
    return M_PI * radius_ * radius_;
}

Point Circle::getCenter() const
{
    return center_;
}

void Circle::move(double xMove, double yMove)
{
    center_.x_ += xMove;
    center_.y_ += yMove;
}

void Circle::scale(double scaleFactor)
{
    radius_ *= scaleFactor;
}

void Circle::printInfo(std::ostream& out) const
{
    Point center = getCenter();
    out << std::setprecision(2) << std::fixed << getName() << ", (" << center.x_ << ", " << center.y_ << "), " << getArea();
}
