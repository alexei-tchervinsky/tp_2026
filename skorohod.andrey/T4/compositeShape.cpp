#include "compositeShape.hpp"

double CompositeShape::getArea() const
{
    int sumArea = 0;
    for (auto &i : shapeContainer_)
    {
        sumArea += i->getArea();
    }
    return sumArea;
}

Point CompositeShape::getCenter() const
{
    Point extremeLeftLower = getLeftLower();
    Point extremeRightUpper = getRightUpper();
    return {((extremeRightUpper.x + extremeLeftLower.x) / 2), ((extremeRightUpper.y + extremeLeftLower.y) / 2)};
}

void CompositeShape::move(double dx, double dy)
{
    for (auto &i : shapeContainer_)
    {
        i->move(dx, dy);
    }
}

void CompositeShape::scale(double k)
{
    double dx, dy;
    Point center_composite = getCenter();
    Point center_i;
    for (auto &i : shapeContainer_)
    {
        center_i = i->getCenter();
        dx = (center_i.x - center_composite.x) * k;
        dy = (center_i.y - center_composite.y) * k;
        i->move(dx, dy);
        i->scale(k);
    }
}

std::string CompositeShape::getName() const
{
    return "COMPOSITE";
}

Point CompositeShape::getLeftLower() const
{
    Point extremeLeftLower = shapeContainer_[0]->getLeftLower();

    for (auto &i : shapeContainer_)
    {
        extremeLeftLower.x = std::min(extremeLeftLower.x, i->getLeftLower().x);
        extremeLeftLower.y = std::min(extremeLeftLower.y, i->getLeftLower().y);
    }

    return extremeLeftLower;
}
Point CompositeShape::getRightUpper() const
{
    Point extremeRightUpper = shapeContainer_[0]->getRightUpper();

    for (auto &i : shapeContainer_)
    {
        extremeRightUpper.x = std::max(extremeRightUpper.x, i->getRightUpper().x);
        extremeRightUpper.y = std::max(extremeRightUpper.y, i->getRightUpper().y);
    }

    return extremeRightUpper;
}

void CompositeShape::addShape(Shape& shape)
{
    shapeContainer_.push_back(&shape);
}

std::ostream& CompositeShape::print(std::ostream& os) const
{
    os << getName() << ' ' << getCenter() << ' ' << getArea() << ":\n";
    for (auto &i : shapeContainer_)
    {
        os << "  " << *i << '\n';
    }
    return os;
}
