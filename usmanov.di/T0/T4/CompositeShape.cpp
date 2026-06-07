#include "CompositeShape.h"
#include <limits>

double CompositeShape::getArea() const
{
    double area = 0.0;
    for (const auto& shapePtr : shapes_) {
        area += shapePtr->getArea();
    }
    return area;
}

Point CompositeShape::getCenter() const
{
    if (shapes_.empty()) {
        return Point();
    }

    double minimumX = std::numeric_limits<double>::max();
    double minimumY = std::numeric_limits<double>::max();
    double maximumX = std::numeric_limits<double>::min();
    double maximumY = std::numeric_limits<double>::min();

    for (const auto& shapePtr : shapes_) {
        Point center = shapePtr->getCenter();
        minimumX = minimumX > center.x_ ? center.x_ : minimumX;
        maximumX = maximumX < center.x_ ? center.x_ : maximumX;
        minimumY = minimumY > center.y_ ? center.y_ : minimumY;
        maximumY = maximumY < center.y_ ? center.y_ : maximumY;
    }

    return Point((minimumX + maximumX) / 2, (minimumY + maximumY) / 2);
}

void CompositeShape::move(double xMove, double yMove)
{
    for (auto& shapePtr : shapes_) {
        shapePtr->move(xMove, yMove);
    }
}

void CompositeShape::scale(double scaleFactor)
{
    Point center = getCenter();

    for (auto& shapePtr : shapes_) {
        Point shapeCenter = shapePtr->getCenter();

        double newX = center.x_ + (shapeCenter.x_ - center.x_) * scaleFactor;
        double newY = center.y_ + (shapeCenter.y_ - center.y_) * scaleFactor;

        shapePtr->move(newX - shapeCenter.x_, newY - shapeCenter.y_);
        shapePtr->scale(scaleFactor);
    }
}

void CompositeShape::printInfo(std::ostream& out) const
{
    Point center = getCenter();
    std::cout << std::fixed << std::setprecision(2) << getName() << ", (" << center.x_ << ", " << center.y_ << "), " << getArea() << ":\n";
    for (auto& shapePtr : shapes_) {
        out << *shapePtr << ",\n";
    }
}
