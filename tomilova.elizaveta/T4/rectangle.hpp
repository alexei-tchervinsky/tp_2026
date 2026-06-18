#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP
#include "shape.hpp"
#include "point.hpp"
class Rectangle : public Shape{
    public:
        Rectangle(const Point & left_low, const Point & right_upper);
        double getArea() const;
        Point getCenter() const;
        void move(double dx, double dy);
        void scale(double coef);
        std::string getName() const;
    private:
        Point left_low_;
        Point right_upper_;
    };

#endif //RECTANGLE_HPP
