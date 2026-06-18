#ifndef COMPOSITE_SHAPE_H
#define COMPOSITE_SHAPE_H

#include "shape.hpp"
#include <memory>
#include <vector>

class CompositeShape : public Shape{
private:
    std::vector<std::shared_ptr<Shape>> shapes_;
public:
    CompositeShape(){}
    void add(const std::shared_ptr<Shape>& shape);
    double getArea()const override;
    Point getCenter() const override;
    void move(double dx, double dy) override;
    void scale(double factor) override;
    std::string getName() const override;
    FrameRect getFrameRect() const override;

};
#endif // COMPOSITE_SHAPE_H
