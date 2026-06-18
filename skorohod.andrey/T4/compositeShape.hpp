#ifndef COMPOSITE_SHAPE_HPP
#define COMPOSITE_SHAPE_HPP

#include <vector>
#include <string>
#include <memory>
#include <algorithm>
#include "shape.hpp"

class CompositeShape : public Shape
{
    public:
    CompositeShape() = default;
    ~CompositeShape() = default;

    double getArea() const;
    Point getCenter() const;
    void move(double, double);
    void scale(double);
    std::string getName() const;

    void addShape(Shape&);

    Point getLeftLower() const;
    Point getRightUpper() const;

    private:
    std::ostream& print (std::ostream& os) const;

    std::vector<Shape*> shapeContainer_;
};

#endif
