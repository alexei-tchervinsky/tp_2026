#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <string>

#include "point.hpp"

class Shape
{
    public:
    virtual double getArea() const = 0;
    virtual Point getCenter() const = 0;
    virtual void move(double, double) = 0;
    virtual void scale(double) = 0;
    virtual std::string getName() const = 0;

    friend std::ostream& operator<< (std::ostream& os, const Shape& shape) {return shape.print(os);}

    virtual Point getLeftLower() const = 0;
    virtual Point getRightUpper() const  = 0;

    protected:
    virtual std::ostream& print (std::ostream& os) const
    {
        os << getName() << ' ' << getCenter() << ' ' << getArea();
        return os;
    }
};

#endif
