#ifndef COMPOSITE_SHAPE_HPP
#define COMPOSITE_SHAPE_HPP

#include "shape.hpp"
#include "point.hpp"
#include <memory>
#include <vector>

namespace golovach {
  class CompositeShape : public Shape {
  public:
    void addShape(std::unique_ptr<Shape> shape);
    double getArea() const override;
    Point getCenter() const override;
    void move(double dx, double dy) override;
    void scale(double factor) override;
    const char* getName() const override;
    const std::vector<std::unique_ptr<Shape>>& getShapes() const;
  private:
    std::vector<std::unique_ptr<Shape>> shapes_;
  };
}

#endif
