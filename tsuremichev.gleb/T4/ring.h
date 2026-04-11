#ifndef RING_H
#define RING_H
#include "point.h"
#include "shape.h"


class Ring: public Shape
{
public:
  // Constructor
  Ring(Point center, double bigRadius, double smallRadius);

  double getArea() const override;
  Point getCenter() const override;
  void move(double dx, double dy) override;
  void scale(double koef) override;
  std::string getName() const override;
  virtual void print() const override;

private:
  Point center_;
  double bigRadius_;
  double smallRadius_;
};


#endif
