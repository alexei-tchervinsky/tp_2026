#ifndef TP_2026_RING_H
#define TP_2026_RING_H

#include "shape.h"

class Ring : public Shape {
private:
    Point center_;
    double outerRadius_;
    double innerRadius_;

public:
    Ring(const Point& center, double outerRadius, double innerRadius);

    double getArea() const override;
    Point getCenter() const override;
    void move(double dx, double dy) override;
    void scale(double factor) override;
    std::string getName() const override;
};

#endif
