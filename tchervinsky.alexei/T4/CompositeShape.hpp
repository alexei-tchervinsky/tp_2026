#ifndef COMPOSITE_SHAPE_HPP
#define COMPOSITE_SHAPE_HPP
#include "Shape.hpp"
#include "Rectangle.hpp"

class CompositeShape
{
private:
	const std::size_t MaxShape{0};
	std::size_t size_{0};
	Shape **array_{nullptr};

public:
	CompositeShape();
	CompositeShape(const CompositeShape &other);
	CompositeShape(CompositeShape &&other) noexcept; // R-value

	~CompositeShape() { delete[] array_; }

	FrameRectangle getFrameRectangle();
	void push_back(Shape &data);
	void move(const double k);
	void scale(const double k);
	Shape *operator[](std::size_t index);
	std::size_t size() const;

	void swap(CompositeShape &other);
	CompositeShape &operator=(const CompositeShape &other);
};

#endif
