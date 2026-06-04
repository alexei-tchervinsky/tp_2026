#ifndef RING_HPP
#define RING_HPP

#include "shape.hpp"
#include "point.hpp"

namespace golovach {
  class Ring : public Shape {
  public:
    Ring(Point center, double outerRadius, double innerRadius);
    double getArea() const override;
    Point getCenter() const override;
    void move(double dx, double dy) override;
    void scale(double factor) override;
    const char* getName() const override;
  private:
    Point center_;
    double outerRadius_;
    double innerRadius_;
  };
}

#endif
