#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "shape.h"

class Rectangle : public Shape {
public:
    Rectangle(const Point& leftBottom, const Point& rightTop);
    Rectangle(const Rectangle& other);
    Rectangle(Rectangle&& other) noexcept;

    Rectangle& operator=(const Rectangle& other);
    Rectangle& operator=(Rectangle&& other) noexcept;

    ~Rectangle() override = default;

    double getArea() const override;
    Point getCenter() const override;
    void move(double dx, double dy) override;
    void scale(double factor) override;
    std::string getName() const override;
    std::unique_ptr<Shape> clone() const override;

private:
    Point leftBottom;
    Point rightTop;

    void swap(Rectangle& other) noexcept;
};

#endif
