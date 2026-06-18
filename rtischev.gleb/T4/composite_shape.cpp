#include "composite_shape.h"

void CompositeShape::addShape(std::unique_ptr<Shape> shape) {
    shapes.push_back(std::move(shape));
}

double CompositeShape::getArea() const {
    double area = 0;
    for (size_t i = 0; i < shapes.size(); ++i){
        area += (*shapes[i]).getArea();
    }
    return area;
}

Point CompositeShape::getCenter() const {
    return getFrameRect().pos;
}

void CompositeShape::move(double dx, double dy) {
    for (size_t i = 0; i < shapes.size(); ++i) {
        (*shapes[i]).move(dx, dy);
    }
}

void CompositeShape::scale(double factor) {
    if (shapes.empty()) return;

    Point Center = getCenter();

    for (size_t i = 0; i < shapes.size(); ++i) {
        Point shapeCenter = shapes[i]->getCenter();

        //на сколько нужно сдвинуть этот центр
        double dx = (shapeCenter.x - Center.x) * (factor - 1.0);
        double dy = (shapeCenter.y - Center.y) * (factor - 1.0);
        shapes[i]->move(dx, dy);

        shapes[i]->scale(factor);
    }
}

std::string CompositeShape::getName() const {
    return "COMPOSITE";
}

FrameRect CompositeShape::getFrameRect() const {
    if (shapes.empty()) {
        return { 0, 0, {0, 0} };
    }

    FrameRect firstFrame = shapes[0]->getFrameRect();
    double minX = firstFrame.pos.x - firstFrame.width / 2.0;
    double maxX = firstFrame.pos.x + firstFrame.width / 2.0;
    double minY = firstFrame.pos.y - firstFrame.height / 2.0;
    double maxY = firstFrame.pos.y + firstFrame.height / 2.0;

    for (size_t i = 1; i < shapes.size(); ++i) {
        FrameRect frame = shapes[i]->getFrameRect();
        double left = frame.pos.x - frame.width / 2.0;
        double right = frame.pos.x + frame.width / 2.0;
        double bottom = frame.pos.y - frame.height / 2.0;
        double top = frame.pos.y + frame.height / 2.0;

        if (left < minX) minX = left;
        if (right > maxX) maxX = right;
        if (bottom < minY) minY = bottom;
        if (top > maxY) maxY = top;
    }

    double width = maxX - minX;
    double height = maxY - minY;
    Point pos = { minX + width / 2.0, minY + height / 2.0 };

    return { width, height, pos };
}

double CompositeShape::getMinX() const { return getFrameRect().pos.x - getFrameRect().width / 2.0; }
double CompositeShape::getMaxX() const { return getFrameRect().pos.x + getFrameRect().width / 2.0; }
double CompositeShape::getMinY() const { return getFrameRect().pos.y - getFrameRect().height / 2.0; }
double CompositeShape::getMaxY() const { return getFrameRect().pos.y + getFrameRect().height / 2.0; }
