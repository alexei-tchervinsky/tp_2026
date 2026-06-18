#ifndef COMPOSITE_SHAPE_H
#define COMPOSITE_SHAPE_H

#include "shape.h"
#include <vector>
#include <memory>
#include <string>


class CompositeShape : public Shape{
private:
    std::vector<std::unique_ptr<Shape>> shapes;

public:
    CompositeShape() = default;
    void addShape(std::unique_ptr<Shape> shape);

    double getArea() const override;
    Point getCenter() const override;
    void move(double dx, double dy) override;
    void scale(double factor) override;
    std::string getName() const override;
    FrameRect getFrameRect() const override;
    double getMinX() const override;
    double getMaxX() const override;
    double getMinY() const override;
    double getMaxY() const override;
};

#endif
