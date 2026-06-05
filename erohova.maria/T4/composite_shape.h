#ifndef COMPOSITE_SHAPE_H
#define COMPOSITE_SHAPE_H

#include <vector>
#include <memory>
#include "shape.h"

class CompositeShape : public Shape {
public:
  CompositeShape() = default;
  void addShape(std::shared_ptr<Shape> shape);

  double getArea() const override;
  Point getCenter() const override;
  void move(double dx, double dy) override;
  void scale(double coefficient) override;
  std::string getName() const override;
  void print() const override;

private:
  std::vector<std::shared_ptr<Shape>> shapes_;
};

#endif
