#ifndef TP_2026_COMPOSITE_SHAPE_H
#define TP_2026_COMPOSITE_SHAPE_H

#include "shape.h"
#include <vector>
#include <memory>

class CompositeShape : public Shape {
private:
    std::vector<std::unique_ptr<Shape>> shapes_;

public:
    CompositeShape() = default;

    void addShape(std::unique_ptr<Shape> shape);

    double getArea() const override;
    Point getCenter() const override;
    void move(double dx, double dy) override;
    void scale(double factor) override;
    std::string getName() const override;

    const std::vector<std::unique_ptr<Shape>>& getShapes() const;
};

#endif
