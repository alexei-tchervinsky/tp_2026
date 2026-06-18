#ifndef SQUARE_HPP
#define SQUARE_HPP

#include "shape.hpp"
#include "point.hpp"

class Square : public Shape {
private:
    Point center;
    float side;
public:
    Square(const Point& center, float side);

    virtual ~Square() override = default;

    virtual float getArea() const override;
    virtual FrameRectangle getFrameRectangle() const override;
    virtual void move(const Point& newPos) override;
    virtual void move(float dx, float dy) override;
    virtual Square* clone() const override;
    virtual std::string getName() const override;

    float getSide() const;
    Point getCenter() const;
};

#endif
