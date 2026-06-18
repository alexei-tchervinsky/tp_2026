#ifndef SQUARE_H
#define SQUARE_H
#include "point.h"
#include "shape.h"


class Square: public Shape
{
public:
  // Constructor
  Square(Point lowerLeft, double side);

  double getArea() const override;
  Point getCenter() const override;
  void move(double dx, double dy) override;
  void scale(double koef) override;
  std::string getName() const override;
  virtual void print() const override;


private:
  Point leftBottom_;
  double side_;
};


#endif
