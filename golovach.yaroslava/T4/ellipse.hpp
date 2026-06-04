#ifndef ELLIPSE_HPP
#define ELLIPSE_HPP

#include "shape.hpp"
#include "point.hpp"

namespace golovach {
  class Ellipse : public Shape {
  public:
    Ellipse(Point center, double verticalRadius, double horizontalRadius);
    double getArea() const override;
    Point getCenter() const override;
    void move(double dx, double dy) override;
    void scale(double factor) override;
    const char* getName() const override;
  private:
    Point center_;
    double verticalRadius_;
    double horizontalRadius_;
  };
}

#endif
