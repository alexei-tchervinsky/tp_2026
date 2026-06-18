#include "Item.hpp"
#include <stdexcept>

Item::Item(int w, int v):
weight_(w),
value_(v)
{
    if (w < 0 || v < 0) throw std::invalid_argument("Weight and value must be non-negative");
}

int Item::getWeight() const
{
    return weight_;
}

int Item::getValue() const
{
    return value_;
}

void Item::setWeight(int w)
{
    weight_ = w;
}

void Item::setValue(int v)
{
    value_ = v;
}

double Item::getDensity() const
{
    if (weight_ == 0) return (value_ == 0) ? 0.0 : 1e9;
    return static_cast<double>(value_) / weight_;
}
