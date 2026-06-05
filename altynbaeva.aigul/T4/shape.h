//абстрактный класс shape
#ifndef SHAPE_H
#define SHAPE_H

#include "point.h"
#include <string>

class Shape {
public:
    virtual ~Shape() = default;
    virtual double getArea() const = 0; //площадь
    virtual Point getCenter() const = 0; //центры
    virtual void move(double dx, double dy) = 0; //сдвинуть
    virtual void scale(double factor) = 0; //увеличить
    virtual std::string getName() const = 0; //название
};

#endif
