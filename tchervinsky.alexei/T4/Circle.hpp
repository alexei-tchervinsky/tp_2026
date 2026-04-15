#ifndef CIRCLE_HPP
#define CIRCLE_HPP
#include "Point.hpp"
#include "FrameRectangle.hpp"
#include "Shape.hpp"
#include <string>

class Circle : public Shape
{
	friend std::ostream &operator<<(std::ostream &out, Circle &c);

private:
	const std::string Name_{"none"};
	Point pos_{0, 0};
	double radius_{0};

public:
	// Конструкторы
	Circle();
	Circle(const std::string &name, const Point &pos, const double &radius);
	// Методы
	double getArea() override;
	FrameRectangle getFrameRectangle() override;
	void move(const double k) override;
	void move(const double x, const double y) override;
	void scale(const double k) override;
	Circle *clone() override;
	std::string getName() const override;
};
#endif
