#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "shape.hpp"


class Rectangle : public Shape{
private:
    Point left_bottom_;
    Point right_top_;
public:
    Rectangle(Point left_bottom, Point right_top): left_bottom_(left_bottom), right_top_(right_top){}
    double getArea() const override;
    Point getCenter() const override;
    void move(double dx, double dy) override;
    void scale(double scale) override;
    std::string getName() const override;
    FrameRect getFrameRect() const override;
};
#endif //RECTANGLE_H
