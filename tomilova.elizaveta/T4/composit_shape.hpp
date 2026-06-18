#ifndef COMPOSIT_SHAPE_HPP
#define COMPOSIT_SHAPE_HPP
#include "shape.hpp"
#include "vector"
#include "memory"
class CompositeShape : public Shape{
    public:
        CompositeShape() = default;
        double getArea() const;
        Point getCenter() const;
        void move(double dx, double dy);
        void scale(double coef);
        std::string getName() const;
        void addShape(std::unique_ptr<Shape> pShape);
        void print() const;
    private:
        std::vector<std::unique_ptr<Shape>> vec_;

};
#endif //COMPOSIT_SHAPE_HPP
