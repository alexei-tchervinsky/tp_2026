#include "ring.hpp"
#include <cmath>

namespace golovach {
  Ring::Ring(Point center, double outerRadius, double innerRadius) :
    center_(center),
    outerRadius_(outerRadius),
    innerRadius_(innerRadius)
  {}

  double Ring::getArea() const {
    return M_PI * (outerRadius_ * outerRadius_ - innerRadius_ * innerRadius_);
  }

  Point Ring::getCenter() const {
    return center_;
  }

  void Ring::move(double dx, double dy) {
    center_.x += dx;
    center_.y += dy;
  }

  void Ring::scale(double factor) {
    outerRadius_ *= factor;
    innerRadius_ *= factor;
  }

  const char* Ring::getName() const {
    return "RING";
  }
}
