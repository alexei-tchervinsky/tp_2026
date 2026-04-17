#ifndef RING_HPP
#define RING_HPP

#include "shape.hpp"

class Ring : public Shape {
private:
    Point center_;
    double innerRadius_;
    double outerRadius_;

public:
    Ring(double x, double y, double inner, double outer);

    double getArea() const override;
    Point getCenter() const override;
    FrameRectangle getFrameRectangle() const override;

    void move(const Point& newPos) override;
    void move(double dx, double dy) override;
    void scale(double coeff) override;
    std::string getName() const override;
};

#endif //!RING_HPP
