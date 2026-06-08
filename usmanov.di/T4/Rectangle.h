#ifndef RECTANGLE_H
#define RECTANGLE_H
#include "shape.h"

class Rectangle : public Shape
{
private:
    Point leftCorner_;
    Point rightCorner_;

    void printInfo(std::ostream& out) const;
public:
    Rectangle() : leftCorner_(Point()), rightCorner_(Point(1, 1)) {}
    Rectangle(Point leftCorner, Point rightCorner)
        : leftCorner_(leftCorner), rightCorner_(rightCorner) {
    }
    Rectangle(double xLeft, double yLeft, double xRight, double yRight)
        : leftCorner_(Point(xLeft, yLeft)), rightCorner_(Point(xRight, yRight)) {
    }

    Rectangle(const Rectangle&) = default;
    Rectangle(Rectangle&&) = default;
    Rectangle& operator=(const Rectangle&) = default;
    Rectangle& operator=(Rectangle&&) = default;

    virtual ~Rectangle() = default;

    double getArea() const;
    Point getCenter()  const;
    void move(double xMove, double yMove);
    void scale(double scaleFactor);
    std::string getName() const { return std::string("RECTANGLE"); }

};
#endif /* RECTANGLE_H */
