#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "shape.hpp"

class Rectangle : public Shape {
private:
    Point center_;
    double width_;
    double height_;

public:
    Rectangle(double x, double y, double width, double height);

    double getArea() const override;
    Point getCenter() const override;
    FrameRectangle getFrameRectangle() const override;

    void move(const Point& newPos) override;
    void move(double dx, double dy) override;
    void scale(double coeff) override;
    std::string getName() const override;
};

#endif //!RECTANGLE_HPP
