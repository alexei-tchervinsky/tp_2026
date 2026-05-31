#ifndef COMPOSITESHAPE_HPP
#define COMPOSITESHAPE_HPP
#include "point.hpp"
#include "shape.hpp"
#include <string>
#include <vector>
#include <memory>
class CompositeShape : public Shape
{
private:
  std::vector<std::shared_ptr<Shape>> shapes;

public:
  CompositeShape();
  void addShape(std::shared_ptr<Shape> shape);
  double getArea() const override;
  Point getCenter() const override;
  void move(double dx, double dy) override;
  void scale(double factor) override;
  std::string getName() const override;
  Point getMinPoint() const override;
  Point getMaxPoint() const override;
};
#endif
