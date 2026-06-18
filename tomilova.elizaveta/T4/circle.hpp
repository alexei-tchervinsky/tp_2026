#ifndef CIRCLE_HPP
#define CIRCLE_HPP
#include "shape.hpp"
#include "point.hpp"
class Circle : public Shape{
    public:
        Circle(const Point & center, double radius);
        double getArea() const;
        Point getCenter() const;
        void move(double dx, double dy);
        void scale(double coef);
        std::string getName() const;
    private:
        Point center_;
        double radius_;
    };

#endif //CIRCLE_HPP
