#include "Rectangle.hpp"

Rectangle::Rectangle() :
	Name_("NewRectangle"),
	pos_(0, 0),
	a_(-0.5, -0.5),
	b_(0.5, 0.5) {}

Rectangle::Rectangle(const std::string& name, Point a, Point b) :
	Name_(name) {
	pos_ = Point((a.GetX() + b.GetX()) / 2, (a.GetY() + b.GetY()) / 2);
	a_ = a;
	b_ = b;
}

double Rectangle::getArea() {
	double width = b_.GetX() - a_.GetX();
	double height = b_.GetY() - a_.GetY();
	return width * height;
}

FrameRectangle Rectangle::getFrameRectangle() {
	double width = b_.GetX() - a_.GetX();
	double height = b_.GetY() - a_.GetY();
	return FrameRectangle(width, height, pos_);
}

void Rectangle::move(const double k) {
	pos_.move(k);
	a_.move(k);
	b_.move(k);
}
void Rectangle::move(const double x, const double y) {
	pos_.SetX(pos_.GetX() + x);
	pos_.SetY(pos_.GetY() + y);
	a_.SetX(a_.GetX() + x);
	a_.SetY(a_.GetY() + y);
	b_.SetX(b_.GetX() + x);
	b_.SetY(b_.GetY() + y);
}

void Rectangle::scale(const double k) {
	Rectangle temp("zero", a_ - pos_, b_ - pos_);// Создаем фигуру в 0,0
	Point temp_pos = pos_; // создаем вектор сдвига
	temp_pos *= k;//умножаем координаты всех точек и вектора сдвига на K
	temp.a_ *= k;
	temp.b_ *= k;
	a_ = temp.a_ + temp_pos;// устанавливаем новые координаты с учетом вектора сдвига
	b_ = temp.b_ + temp_pos;
}

Rectangle* Rectangle::clone() {
	Rectangle* copy = new Rectangle("Copy", a_, b_);
	return copy;
}

std::string Rectangle::getName() const {
	return Name_;
}

std::ostream& operator << (std::ostream& out, Rectangle& R) {
	FrameRectangle temp = R.getFrameRectangle();
	Point a(temp.pos_.GetX() - temp.WIDTH / 2, temp.pos_.GetY() - temp.HEIGHT / 2);
	Point b(temp.pos_.GetX() + temp.WIDTH / 2, temp.pos_.GetY() + temp.HEIGHT / 2);
	out << R.getName() << " " << round(R.getArea() * 10) / 10 << " " << a << " " << b;
	return out;
}