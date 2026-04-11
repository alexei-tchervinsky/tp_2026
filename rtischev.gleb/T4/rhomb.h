#ifndef RHOM_H
#define RHOM_H

#include "shape.h"
#include "point.h"

class Rhombus : public Shape{
private:
    Point center;
    double hHalf;
    double vHalf;

public:
    Rhombus(Point center, double hHalf, double vHalf);
    double getArea() const override;
    Point getCenter() const override;
    void move(double dx, double dy) override;
    void scale(double factor) override;
    std::string getName() const override;
    FrameRect getFrameRect() const override;
    double getMinX() const override;
    double getMaxX() const override;
    double getMinY() const override;
    double getMaxY() const override;
};

#endif
