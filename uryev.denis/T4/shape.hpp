#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <string>
#include "point.hpp"

struct FrameRectangle {
    double width_;
    double height_;
    Point pos_;
};

class Shape {
public:
    virtual ~Shape() = default;
    virtual double getArea() const = 0;
    virtual Point getCenter() const = 0;
    virtual FrameRectangle getFrameRectangle() const = 0;
    virtual void move(const Point& newPos) = 0;
    virtual void move(double dx, double dy) = 0;
    virtual void scale(double coeff) = 0;
    virtual std::string getName() const = 0;
};

#endif //!SHAPE_HPP
