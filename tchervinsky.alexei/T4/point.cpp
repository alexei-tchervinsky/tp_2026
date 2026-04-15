#include "Point.hpp"

bool Point::isEqual(const Point &other)
{
	return (other.x_ == x_ && other.y_ == y_);
}

void Point::move(const double K)
{
	x_ += K;
	y_ += K;
}
double Point::getDistance(const Point &other)
{
	return sqrt((other.x_ - x_) * (other.x_ - x_) + (other.y_ - y_) * (other.y_ - y_));
}

Point::Point()
{
	x_ = 0.0;
	y_ = 0.0;
}
Point::Point(double x, double y)
{
	x_ = x;
	y_ = y;
}

std::ostream &operator<<(std::ostream &out, const Point &p)
{
	out << round(p.x_ * 10) / 10 << " " << round(p.y_ * 10) / 10;
	return out;
}

std::istream &operator>>(std::istream &in, Point &p)
{
	in >> p.x_ >> p.y_;
	return in;
}

Point Point::operator+(const Point &other)
{
	return Point(x_ + other.x_, y_ + other.y_);
}

Point Point::operator-(const Point &other)
{
	return Point(x_ - other.x_, y_ - other.y_);
}

Point &Point::operator*=(const double K)
{
	x_ *= K;
	y_ *= K;
	return *this;
}

Point &Point::operator++()
{
	x_++;
	y_++;
	return *this;
}
