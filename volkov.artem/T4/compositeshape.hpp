#ifndef COMPOSITESHAPE_HPP
#define COMPOSITESHAPE_HPP

#include "shape.hpp"
#include <vector>
#include <memory>

class CompositeShape : public Shape {
private:
    std::vector<std::shared_ptr<Shape> > shapes;

public:
    void addShape(const std::shared_ptr<Shape> &shape);

    double getArea() const override;

    Point getCenter() const override;

    void move(double dx, double dy) override;

    void scale(double factor) override;

    std::string getName() const override;

    const std::vector<std::shared_ptr<Shape> > &getShapes() const;
};

#endif
