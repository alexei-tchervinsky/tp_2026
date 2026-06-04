#include "ellipse.hpp"
#include <cmath>

namespace golovach {
  Ellipse::Ellipse(Point center, double verticalRadius, double horizontalRadius) :
    center_(center),
    verticalRadius_(verticalRadius),
    horizontalRadius_(horizontalRadius)
  {}

  double Ellipse::getArea() const {
    return M_PI * verticalRadius_ * horizontalRadius_;
  }

  Point Ellipse::getCenter() const {
    return center_;
  }

  void Ellipse::move(double dx, double dy) {
    center_.x += dx;
    center_.y += dy;
  }

  void Ellipse::scale(double factor) {
    verticalRadius_ *= factor;
    horizontalRadius_ *= factor;
  }

  const char* Ellipse::getName() const {
    return "ELLIPSE";
  }
}
