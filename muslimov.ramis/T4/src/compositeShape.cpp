#include "../include/compositeShape.hpp"
#include <stdexcept>
#include <limits>
#include <utility>

void CompositeShape::add(std::unique_ptr<Shape> shape)
{
    if(!shape) return;
    if (shape.get() == this) {
        throw std::invalid_argument("CompositeShape::add: cannot add composite to itself");
    }
    shapes_.push_back(std::move(shape));
}

std::size_t CompositeShape::size() const noexcept
{
    return shapes_.size();
}

double CompositeShape::getArea() const
{
    if(shapes_.empty()){
        return 0.0;
    }
    double sum = 0.0;
    for(const auto &s : shapes_){
        sum += s->getArea();
    }
    return sum;
}

void CompositeShape::getBoundingBox(double &left, double &bottom, double &right, double &top) const
{
    if(shapes_.empty()){
        left = bottom = right = top = 0.0;
        return;
    }

    left = std::numeric_limits<double>::infinity();
    bottom = std::numeric_limits<double>::infinity();
    right = -std::numeric_limits<double>::infinity();
    top = -std::numeric_limits<double>::infinity();

    for (const auto& s : shapes_){
        double l, b, r, t;
        s->getBoundingBox(l, b, r, t);
        if(l < left) left = l;
        if(b < bottom) bottom = b;
        if(r > right) right = r;
        if(t > top) top = t;

    }
}
Point CompositeShape::getCenter() const
{
    if(shapes_.empty()){
        throw std::runtime_error("CompositeShape::getCenter: composite is empty");
    }
    double l, b, r, t;
    getBoundingBox(l, b, r, t);
    return Point { (l + r)/2.0, (b + t)/2.0 };
}

void CompositeShape::move(double dx, double dy)
{
    for(auto &s : shapes_){
        s->move(dx, dy);
    }
}

void CompositeShape::scale(double factor)
{
    if(!(factor > 0.0)){
        throw std::invalid_argument("CompositeShape::scale: factor must be > 0");
    }
    if(shapes_.empty()) return;

    Point center = getCenter();

    // Для каждой фигуры: сместить центр и масштабировать
    for(auto &s : shapes_)
    {
        Point p = s->getCenter();
        double vx = p.x - center.x;
        double vy = p.y - center.y;

        Point newP {center.x + vx * factor, center.y + vy * factor};
        double dx = newP.x - p.x;
        double dy = newP.y - p.y;

        s->move(dx, dy);
        s->scale(factor);
    }
}

std::string CompositeShape::getName() const {
    return "COMPOSITE";
}
