#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "point.hpp"
#include "shape.hpp"

class Circle : public Shape
{
    public:
    Circle(Point, double);
    ~Circle() = default;

    double getArea() const;
    Point getCenter() const;
    void move(double, double);
    void scale(double);
    std::string getName() const;

    Point getLeftLower() const;
    Point getRightUpper() const;

    private:
    Point center_;
    double radius_;
};

#endif
