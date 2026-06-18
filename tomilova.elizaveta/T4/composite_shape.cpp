#include "composit_shape.hpp"
#include <iostream>
#include <stdexcept>
double CompositeShape::getArea() const{
    double total_area = 0.0;
    for (size_t i = 0; i < vec_.size(); i++){
        total_area += vec_[i]->getArea();
    }
    return total_area;
}
Point CompositeShape::getCenter() const{
    if (vec_.empty()) {
        throw std::logic_error("Composite shape is empty");
    }
    double minX = vec_[0]->getCenter().x;
    double maxX = vec_[0]->getCenter().x;
    double minY = vec_[0]->getCenter().y;
    double maxY = vec_[0]->getCenter().y;
    for (size_t i = 1; i < vec_.size(); i++){
        Point c = vec_[i]->getCenter();
        if (c.x < minX) minX = c.x;
        if (c.x > maxX) maxX = c.x;
        if (c.y < minY) minY = c.y;
        if (c.y > maxY) maxY = c.y;
    }
    return {(minX + maxX)/2, (minY + maxY)/2};
}
void CompositeShape::move(double dx, double dy){
    for (size_t i = 0; i < vec_.size(); i++){
        vec_[i]->move(dx, dy);
    }
}

void CompositeShape::scale(double coef){
    if (coef < 0.0){
        throw std::invalid_argument("Coef must pe positive");
    }
    Point compositeCenter = getCenter();
    for (size_t i = 1; i < vec_.size(); i++){
        Point figureCenter = vec_[i]->getCenter();

        double dx = (figureCenter.x - compositeCenter.x)*(coef - 1.0);
        double dy = (figureCenter.y - compositeCenter.y)*(coef - 1.0);
        vec_[i]->move(dx, dy);

        vec_[i]->scale(coef);
    }
}

std::string CompositeShape::getName() const{
    return "CompositeShape";
}

void CompositeShape::addShape(std::unique_ptr<Shape> pShape){
    if (pShape != nullptr){
        vec_.push_back(std::move(pShape));
    }
}

void CompositeShape::print() const {
    Point c = getCenter();
    std::cout << "[COMPOSITE, (" << c.x << ", " << c.y <<
    "), " << getArea() << ":" << std::endl;
    for (size_t i = 0; i < vec_.size(); ++i) {
        Point fCen = vec_[i]->getCenter();
        std::cout << " " << vec_[i]->getName()
        << ", (" << fCen.x << ", " << fCen.y << "), "
         << vec_[i]->getArea();
        if (i < vec_.size() - 1) std::cout << ",";
        std::cout << '\n';
    }
    std::cout << "]" << '\n';
}
