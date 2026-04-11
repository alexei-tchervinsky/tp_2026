#ifndef COMPOSITE_SHAPE_H
#define COMPOSITE_SHAPE_H
#include <memory>
#include <string>
#include <vector>

#include "point.h"
#include "shape.h"

class CompositeShape: public Shape {
public:
  CompositeShape() = default;
  double getArea() const override;
  Point getCenter() const override;
  void move(double dx, double dy) override;
  void scale(double koef) override;
  std::string getName() const override;
  void print() const override;

  void addShape(std::unique_ptr<Shape> shape);


private:
  std::vector<std::unique_ptr<Shape>> shapes_;
};

#endif
