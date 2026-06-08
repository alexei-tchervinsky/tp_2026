#ifndef SHAPE_H
#define SHAPE_H
#include <iostream>
#include <iomanip>
#include <string>
#include "point.h"
#include "ScopeGuard.h"

class Shape
{
private:
    virtual void printInfo(std::ostream& out) const = 0;
public:
    virtual double getArea() const = 0;
    virtual Point getCenter()  const = 0;
    virtual void move(double xMove, double yMove) = 0;
    virtual void scale(double scaleFactor) = 0;
    virtual std::string getName() const = 0;
    friend std::ostream& operator<<(std::ostream& out, const Shape& shape);

    virtual ~Shape() = default;
};

inline std::ostream& operator<<(std::ostream& out, const Shape& shape) {
    StreamGuard guard(out);
    shape.printInfo(out);
    return out;
}
#endif /* SHAPE_H */
