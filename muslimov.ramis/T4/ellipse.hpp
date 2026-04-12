#ifndef ELLIPSE_HPP
#define ELLIPSE_HPP
#include "shape.hpp"
#include "point.hpp"
#include <string>

class Ellipse : public Shape
{
public:
    Ellipse (const Point& center, double verticalRadius, double horizontalRadius);

    double getArea() const override;
    Point getCenter() const override;
    void move(double dx, double dy) override;
    void scale(double factor) override;
    std::string getName() const override;

    double left() const;
    double right() const;
    double bottom() const;
    double top() const;

    void getBoundingBox(double &left, double &bottom, double &right, double &top) const override;

private:
    Point center_;
    double ry_;
    double rx_;

    static void validateRadius(double ry, double rx);
};


#endif //ELLIPSE_HPP
