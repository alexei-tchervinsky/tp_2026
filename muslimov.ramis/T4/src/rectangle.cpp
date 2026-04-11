#include "../include/rectangle.hpp"
#include <stdexcept>
#include <cmath>

namespace{
    constexpr double EPS = 1e-12;
}


Rectangle::Rectangle(const Point & leftBottom, const Point & rightTop)
    : leftBottom_(leftBottom), rightTop_(rightTop)
{
    validateCorners(leftBottom_, rightTop_);
}

void Rectangle::validateCorners(const Point & lb, const Point & rt){

    double width = rt.x - lb.x;
    double height = rt.y - lb.y;

    if(width <= EPS || height <= EPS){
        throw std::invalid_argument("Rectangle::validateCorners: rightTop must be strictly to the right and above leftBottom");
    }
}

double Rectangle::getArea() const
{
    return getWidth() * getHeight();
}

Point Rectangle::getCenter() const
{
    return Point {(leftBottom_.x + rightTop_.x) / 2.0, (leftBottom_.y + rightTop_.y) / 2.0};
}

void Rectangle::move(double dx, double dy)
{
    leftBottom_.x += dx;
    leftBottom_.y += dy;
    rightTop_.x += dx;
    rightTop_.y += dy;
}

void Rectangle::scale(double factor)
{
    if(!(factor > 0.0)){
        throw std::invalid_argument("Rectangle::scale: Factor must be > 0");
    }

    Point c = getCenter();

    //Вектор от центра до левой нижней точки
    double lb_dx = leftBottom_.x - c.x;
    double lb_dy = leftBottom_.y - c.y;

    //Вектор от центра до правой верхней точки
    double rt_dx = rightTop_.x - c.x;
    double rt_dy = rightTop_.y - c.y;

    //Массштабируем векторы и восстанавливаем углы
    leftBottom_.x = c.x + lb_dx * factor;
    leftBottom_.y = c.y + lb_dy * factor;

    rightTop_.x = c.x + rt_dx * factor;
    rightTop_.y = c.y + rt_dy * factor;

    //По идее порядок должен сохраняться при Factor > 0, но проверка на всякий случай
    validateCorners(leftBottom_, rightTop_);
}

std::string Rectangle::getName() const
{
    return "RECTANGLE";
}

double Rectangle::getWidth() const
{
    return rightTop_.x - leftBottom_.x;
}

double Rectangle::getHeight() const
{
    return rightTop_.y - leftBottom_.y;
}

Point Rectangle::getLeftBottom() const
{
    return leftBottom_;
}

Point Rectangle::getRightTop() const
{
    return rightTop_;
}

void Rectangle::getBoundingBox(double &left, double &bottom, double &right, double &top) const {
    left = leftBottom_.x;
    bottom = leftBottom_.y;
    right = rightTop_.x;
    top = rightTop_.y;
}
