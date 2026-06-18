#include "Rectangle.h"

double Rectangle::getArea() const
{
    double sideOne = leftCorner_.getDistance(rightCorner_.x_, leftCorner_.y_);
    double sideTwo = leftCorner_.getDistance(leftCorner_.x_, rightCorner_.y_);
    return sideOne * sideTwo;
}

Point Rectangle::getCenter() const
{
    return Point((rightCorner_.x_ + leftCorner_.x_) / 2,
        (rightCorner_.y_ + leftCorner_.y_) / 2);
}

void Rectangle::move(double xMove, double yMove)
{
    leftCorner_.x_ += xMove;
    leftCorner_.y_ += yMove;
    rightCorner_.x_ += xMove;
    rightCorner_.y_ += yMove;
}

void Rectangle::scale(double scaleFactor)
{
    Point center = getCenter();

    leftCorner_.x_ = center.x_ - (center.x_ - leftCorner_.x_) * scaleFactor;
    leftCorner_.y_ = center.y_ - (center.y_ - leftCorner_.y_) * scaleFactor;
    rightCorner_.x_ = center.x_ + (rightCorner_.x_ - center.x_) * scaleFactor;
    rightCorner_.y_ = center.y_ + (rightCorner_.y_ - center.y_) * scaleFactor;
}

void Rectangle::printInfo(std::ostream& out) const
{
    Point center = getCenter();
    out << std::setprecision(2) << std::fixed << getName() << ", (" << center.x_ << ", " << center.y_ << "), " << getArea();
}
