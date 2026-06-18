#ifndef COMPOSITE_SHAPE_HPP
#define COMPOSITE_SHAPE_HPP

#include <vector>
#include <memory>

#include "shape.hpp"

class CompositeShape : public Shape {
public:
    void add(std::unique_ptr<Shape> s);
    double getArea() const override;
    Point getCenter() const override;
    void move(double dx, double dy) override;
    void scale(double koef) override;
    std::string getName() const override;
    void print() const override;
private:
    std::vector<std::unique_ptr<Shape>> shapes;
};

#endif
