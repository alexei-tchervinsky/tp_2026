#include "compositeshape.h"
#include <stdexcept>

void CompositeShape::addShape(std::unique_ptr<Shape> shape)
{
    if (!shape)
    {
        throw std::invalid_argument("Null shape cannot be added");
    }

    shapes.push_back(std::move(shape));
}

double CompositeShape::getArea() const
{
    double totalArea = 0.0;
    for (const auto& shape : shapes)
    {
        totalArea += shape->getArea();
    }
    return totalArea;
}

Point CompositeShape::getCenter() const
{
    if (shapes.empty())
    {
        throw std::logic_error("CompositeShape is empty");
    }

    double left = shapes[0]->getLeft();
    double right = shapes[0]->getRight();
    double bottom = shapes[0]->getBottom();
    double top = shapes[0]->getTop();

    for (const auto& shape : shapes)
    {
        if (shape->getLeft() < left) left = shape->getLeft();
        if (shape->getRight() > right) right = shape->getRight();
        if (shape->getBottom() < bottom) bottom = shape->getBottom();
        if (shape->getTop() > top) top = shape->getTop();
    }

    return Point{(left + right) / 2.0, (bottom + top) / 2.0};
}

void CompositeShape::move(double dx, double dy)
{
    for (auto& shape : shapes)
    {
        shape->move(dx, dy);
    }
}

void CompositeShape::scale(double factor)
{
    if (factor <= 0)
    {
        throw std::invalid_argument("Scale factor must be positive");
    }

    Point compositeCenter = getCenter();

    for (auto& shape : shapes)
    {
        Point shapeCenter = shape->getCenter();

        double dx = shapeCenter.x - compositeCenter.x;
        double dy = shapeCenter.y - compositeCenter.y;

        double newDx = dx * factor;
        double newDy = dy * factor;

        shape->move(newDx - dx, newDy - dy);
        shape->scale(factor);
    }
}

std::string CompositeShape::getName() const
{
    return "COMPOSITE";
}

double CompositeShape::getLeft() const
{
    if (shapes.empty())
    {
        throw std::logic_error("CompositeShape is empty");
    }

    double left = shapes[0]->getLeft();
    for (const auto& shape : shapes)
    {
        if (shape->getLeft() < left) left = shape->getLeft();
    }
    return left;
}

double CompositeShape::getRight() const
{
    if (shapes.empty())
    {
        throw std::logic_error("CompositeShape is empty");
    }

    double right = shapes[0]->getRight();
    for (const auto& shape : shapes)
    {
        if (shape->getRight() > right) right = shape->getRight();
    }
    return right;
}

double CompositeShape::getBottom() const
{
    if (shapes.empty())
    {
        throw std::logic_error("CompositeShape is empty");
    }

    double bottom = shapes[0]->getBottom();
    for (const auto& shape : shapes)
    {
        if (shape->getBottom() < bottom) bottom = shape->getBottom();
    }
    return bottom;
}

double CompositeShape::getTop() const
{
    if (shapes.empty())
    {
        throw std::logic_error("CompositeShape is empty");
    }

    double top = shapes[0]->getTop();
    for (const auto& shape : shapes)
    {
        if (shape->getTop() > top) top = shape->getTop();
    }
    return top;
}

const std::vector<std::unique_ptr<Shape>>& CompositeShape::getShapes() const
{
    return shapes;
}
