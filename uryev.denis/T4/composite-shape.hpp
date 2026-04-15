#ifndef COMPOSITE_SHAPE_HPP
#define COMPOSITE_SHAPE_HPP

#include "shape.hpp"

class CompositeShape : public Shape {
private:
    Shape** shapes_;
    std::size_t size_;
    std::size_t capacity_;

public:
    CompositeShape(std::size_t capacity);
    ~CompositeShape();

    void addShape(Shape* shape);

    double getArea() const override;
    Point getCenter() const override;
    FrameRectangle getFrameRectangle() const override;

    void move(const Point& newPos) override;
    void move(double dx, double dy) override;
    void scale(double coeff) override;
    std::string getName() const override;
};

#endif //!COMPOSITE_SHAPE_HPP
