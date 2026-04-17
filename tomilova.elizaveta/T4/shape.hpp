#ifndef SHAPE_HPP
#define SHAPE_HPP
#include <string>
#include "point.hpp"
class Shape{
    public:
    virtual ~Shape() = default;
    virtual double getArea() const = 0;
    virtual Point getCenter() const = 0;
    virtual void move(double dx, double dy) = 0;
    virtual void scale(double coefficient) = 0;
    virtual std::string getName() const = 0;
};
#endif //SHAPE_HPP
