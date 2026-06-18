#ifndef CIRCLE_H
#define CIRCLE_H

#include "shape.h"

class Circle : public Shape {
public:
    Circle(const Point& center, double radius);
    Circle(const Circle& other);
    Circle(Circle&& other) noexcept;

    Circle& operator=(const Circle& other);
    Circle& operator=(Circle&& other) noexcept;

    ~Circle() override = default;

    double getArea() const override;
    Point getCenter() const override;
    void move(double dx, double dy) override;
    void scale(double factor) override;
    std::string getName() const override;
    std::unique_ptr<Shape> clone() const override;

private:
    Point center;
    double radius;

    void swap(Circle& other) noexcept;
};

#endif
