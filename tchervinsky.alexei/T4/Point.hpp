#ifndef POINT_HPP
#define POINT_HPP
#include <iostream>
#include <math.h>

class Point
{
private:
	double x_{0.0};
	double y_{0.0};

public:
	Point();
	Point(double x, double y);
	void SetX(const double new_x) { x_ = new_x; }
	void SetY(const double new_y) { y_ = new_y; }
	double GetX() { return x_; }
	double GetY() { return y_; }
	bool isEqual(const Point &other);
	void move(const double K);
	double getDistance(const Point &other);

	bool operator==(const Point &other) { return x_ == other.x_ && y_ == other.y_; }
	bool operator<(const Point &other) { return x_ < other.x_ && y_ < other.y_; }

	friend std::ostream &operator<<(std::ostream &out, const Point &p);
	friend std::istream &operator>>(std::istream &in, Point &p);

	Point &operator++();
	Point operator+(const Point &other);
	Point operator-(const Point &other);
	Point &operator*=(const double K);
};

#endif
