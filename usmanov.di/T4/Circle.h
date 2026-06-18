#ifndef CIRCLE_H
#define CIRCLE_H
#include "shape.h"

class Circle : public Shape
{
private:
    Point center_;
    double radius_;

    void printInfo(std::ostream& out) const;
public:
    Circle() : center_(Point()), radius_(1) {}
    Circle(Point center, double radius)
        : center_(center), radius_(radius) {
    }
    Circle(double x, double y, double radius)
        : center_(Point(x, y)), radius_(radius) {
    }

    Circle(const Circle&) = default;
    Circle(Circle&&) = default;
    Circle& operator=(const Circle&) = default;
    Circle& operator=(Circle&&) = default;

    virtual ~Circle() = default;

    double getArea() const;
    Point getCenter()  const;
    void move(double xMove, double yMove);
    void scale(double scaleFactor);
    std::string getName() const { return std::string("CIRCLE"); }
};
#endif /* CIRCLE_H */
