#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "../include/point.hpp"
#include <string>

class Shape{
public:
    virtual ~Shape() = default;
    virtual double getArea() const = 0;
    virtual Point getCenter() const = 0;
    virtual void move(double dx, double dy) = 0;
    virtual void scale(double factor) = 0;
    virtual std::string getName() const = 0;

    virtual void getBoundingBox(double &left, double &bottom, double &right, double &top) const = 0;
};

#endif //SHAPE_HPP
