#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "shape.hpp"
#include "point.hpp"

class Rectangle : public Shape
{
    public:
    Rectangle(Point&, Point&);
    ~Rectangle() = default;

    double getArea() const; 
    Point getCenter() const;
    void move(double, double);
    void scale(double);
    std::string getName() const;

    private:
    Point vertex1_, vertex2_, center_;
};

#endif