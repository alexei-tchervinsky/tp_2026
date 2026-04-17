//
//  circle.hpp
//  OOP
//
//  Created by Тимур Ахметханов on 21.12.2024.
//

#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "point.hpp"
#include "shape.hpp"

class Circle : public Shape {
private:
    Point center;
    float radius;

public:
    Circle(const Point& center, float radius);

    virtual ~Circle() override = default;

    virtual float getArea() const override;
    virtual FrameRectangle getFrameRectangle() const override;
    virtual void move(const Point& newPos) override;
    virtual void move(float dx, float dy) override;
    virtual Circle* clone() const override;
    virtual std::string getName() const override;
    float getRadius() const;
    Point getCenter() const;

};

#endif
