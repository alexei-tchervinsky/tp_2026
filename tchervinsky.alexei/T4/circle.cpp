#include "Circle.hpp"
double const PI = 3.14;

Circle::Circle() : Name_("NewCircle"),
									 pos_(0, 0),
									 radius_(1) {}

Circle::Circle(const std::string &name, const Point &pos, const double &radius) : Name_(name)
{
	pos_ = pos;
	radius_ = radius;
}

double Circle::getArea()
{
	return PI * radius_ * radius_;
}

FrameRectangle Circle::getFrameRectangle()
{
	return FrameRectangle(radius_ * 2, radius_ * 2, pos_);
}

void Circle::move(const double k)
{
	pos_.move(k);
}

void Circle::move(const double x, const double y)
{
	pos_.SetX(pos_.GetX() + x);
	pos_.SetY(pos_.GetY() + y);
}

void Circle::scale(const double k)
{
	Circle temp("zero", pos_ - pos_, radius_);
	Point temp_pos = pos_;
	temp_pos *= k;
	temp.radius_ *= k;
	radius_ = temp.radius_;
	pos_ = temp_pos;
}

Circle *Circle::clone()
{
	Circle *copy = new Circle("copy", pos_, radius_);
	return copy;
}

std::string Circle::getName() const
{
	return Name_;
}

std::ostream &operator<<(std::ostream &out, Circle &c)
{
	FrameRectangle temp = c.getFrameRectangle();
	Point a(temp.pos_.GetX() + temp.WIDTH / 2, temp.pos_.GetY() + temp.HEIGHT / 2);
	Point b(temp.pos_.GetX() - temp.WIDTH / 2, temp.pos_.GetY() - temp.HEIGHT / 2);
	out << c.getName() << " " << round(c.getArea() * 10) / 10 << " " << a << " " << b;
	return out;
}
