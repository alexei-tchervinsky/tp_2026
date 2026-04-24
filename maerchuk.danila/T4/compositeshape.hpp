#ifndef COMPOSITESHAPE_HPP
#define COMPOSITESHAPE_HPP

#include <vector>
#include <string>
#include "shape.hpp"

class CompositeShape : public Shape {
public:
    CompositeShape() = default;

    CompositeShape(const CompositeShape&) = default;
    CompositeShape(CompositeShape&&) noexcept = default;
    CompositeShape& operator=(const CompositeShape&) = default;
    CompositeShape& operator=(CompositeShape&&) noexcept = default;

    ~CompositeShape() override = default;

    void add(Shape* shape);
    void remove(size_t index);

    float getArea() const override;
    FrameRectangle getFrameRectangle() const override;
    void move(const Point& newPos) override;
    void move(float dx, float dy) override;

    void scale(float factor);

    CompositeShape* clone() const override;
    std::string getName() const override;

private:
    std::vector<Shape*> shapes_;
};

#endif
