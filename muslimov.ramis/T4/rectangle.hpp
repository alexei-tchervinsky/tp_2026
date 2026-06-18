#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "point.hpp"
#include "shape.hpp"

class Rectangle : public Shape
{
public:
    Rectangle(const Point& leftBottom, const Point& rightTop);
    double getArea() const override;
    Point getCenter() const override;
    void move(double dx, double dy) override;
    void scale(double factor) override;
    std::string getName() const override;

    double getWidth() const;
    double getHeight() const;
    Point getLeftBottom() const;
    Point getRightTop() const;

    void getBoundingBox(double &left, double &bottom, double &right, double &top) const override;

private:
    Point leftBottom_;
    Point rightTop_;

    static void validateCorners(const Point& lb, const Point& rt);
};

#endif //RECTANGLE_HPP
