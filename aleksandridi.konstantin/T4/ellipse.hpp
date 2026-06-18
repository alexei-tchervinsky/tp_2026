#ifndef ELLIPSE_H
#define ELLIPSE_H

#include "shape.hpp"

class Ellipse : public Shape{
private:
    Point center_;
    double horizontalRadius_;
    double verticalRadius_;
public:
    Ellipse(Point center, double horizontalRadius, double verticalRadius):
        center_(center), horizontalRadius_(horizontalRadius), verticalRadius_(verticalRadius){}
    double getArea() const override;
    Point getCenter() const override;
    void move(double dx, double dy) override;
    void scale(double factor) override;
    std::string getName() const override;
    FrameRect getFrameRect() const override;
};
#endif // ELLIPSE_H
