#ifndef SHAPES_HPP
#define SHAPES_HPP

#include <string>

class Point {
public:
    double x, y;
    Point(double x_val = 0.0, double y_val = 0.0);
};

class FrameRectangle {
public:
    double width, height;
    Point center;
    FrameRectangle(double w = 0.0, double h = 0.0, Point c = Point());
    Point getBottomLeft() const;
    Point getTopRight() const;
};

class Shape {
public:
    virtual ~Shape() {}
    virtual double area() const = 0;
    virtual FrameRectangle getFrame() const = 0;
    virtual void move(const Point &newPos) = 0;
    virtual void move(double dx, double dy) = 0;
    virtual void scale(double factor) = 0;
    virtual Shape *clone() const = 0;
    virtual std::string getName() const = 0;
};

class Rectangle : public Shape {
private:
    Point center;
    double width, height;
public:
    Rectangle(const Point &c, double w, double h);
    double area() const override;
    FrameRectangle getFrame() const override;
    void move(const Point &newPos) override;
    void move(double dx, double dy) override;
    void scale(double factor) override;
    Shape *clone() const override;
    std::string getName() const override;
};

class Ring : public Shape {
private:
    Point center;
    double innerRadius, outerRadius;
public:
    Ring(const Point &c, double inner_r, double outer_r);
    double area() const override;
    FrameRectangle getFrame() const override;
    void move(const Point &newPos) override;
    void move(double dx, double dy) override;
    void scale(double factor) override;
    Shape *clone() const override;
    std::string getName() const override;
};

class Square : public Shape {
private:
    Point center;
    double side;
public:
    Square(const Point &c, double side_length);
    double area() const override;
    FrameRectangle getFrame() const override;
    void move(const Point &newPos) override;
    void move(double dx, double dy) override;
    void scale(double factor) override;
    Shape *clone() const override;
    std::string getName() const override;
};

class Circle : public Shape {
private:
    Point center;
    double radius;
public:
    Circle(const Point &c, double r);
    double area() const override;
    FrameRectangle getFrame() const override;
    void move(const Point &newPos) override;
    void move(double dx, double dy) override;
    void scale(double factor) override;
    Shape *clone() const override;
    std::string getName() const override;
};

class CompositeShape : public Shape {
private:
    Shape **shapes;
    size_t count, maxShapes;
    Point center;
    void updateCenter();
public:
    CompositeShape(size_t max_s);
    ~CompositeShape();
    void addShape(Shape *shape);
    double area() const override;
    FrameRectangle getFrame() const override;
    void move(const Point &newPos) override;
    void move(double dx, double dy) override;
    void scale(double factor) override;
    Shape *clone() const override;
    std::string getName() const override;
};

#endif
