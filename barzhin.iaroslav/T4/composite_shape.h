//
// Created by xmdnusr on 07.03.2026.
//

#ifndef T4_COMPOSITE_SHAPE_H
#define T4_COMPOSITE_SHAPE_H
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
    void scale(double coefficient) override;
    std::string getName() const override;
    void print() const override;

    void addShape(std::unique_ptr<Shape> shape);

    // misc
    Point getLeftLow() const override;
    Point getRightTop() const override;
private:
    std::vector<std::unique_ptr<Shape>> vec_;
};

#endif //T4_COMPOSITE_SHAPE_H
