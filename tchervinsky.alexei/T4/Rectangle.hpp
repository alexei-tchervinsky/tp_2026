#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP
#include "Shape.hpp"

class Rectangle : public Shape
{
	friend std::ostream &operator<<(std::ostream &out, Rectangle &R);

private:
	const std::string Name_{"none"};
	Point pos_{0, 0};
	Point a_{0, 0};
	Point b_{0, 0};

public:
	// Конструкторы
	Rectangle();
	Rectangle(const std::string &name, Point a, Point b);
	// Методы
	double getArea() override;
	FrameRectangle getFrameRectangle() override;
	void move(const double k) override;
	void move(const double x, const double y) override;
	void scale(const double k) override;
	Rectangle *clone() override;
	std::string getName() const override;
};
#endif
