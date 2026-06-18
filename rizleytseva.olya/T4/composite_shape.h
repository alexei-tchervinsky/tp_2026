#ifndef COMPOSITE_SHAPE_H
#define COMPOSITE_SHAPE_H

#include "shape.h"
#include <vector>
#include <memory>

class CompositeShape : public Shape {
public:
    CompositeShape() = default;
    CompositeShape(const CompositeShape& other);
    CompositeShape(CompositeShape&& other) noexcept;

    CompositeShape& operator=(const CompositeShape& other);
    CompositeShape& operator=(CompositeShape&& other) noexcept;

    ~CompositeShape() override = default;

    void addShape(std::unique_ptr<Shape> shape);

    double getArea() const override;
    Point getCenter() const override;
    void move(double dx, double dy) override;
    void scale(double factor) override;
    std::string getName() const override;
    std::unique_ptr<Shape> clone() const override;

    const std::vector<std::unique_ptr<Shape>>& getShapes() const;

private:
    std::vector<std::unique_ptr<Shape>> shapes;

    void swap(CompositeShape& other) noexcept;
};

#endif
