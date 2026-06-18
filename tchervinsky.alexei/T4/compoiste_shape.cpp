#include "CompositeShape.hpp"
#include <limits>

double max(double a, double b) {
  if (a < b) {
    return b;
  }
  return a;
}
double min(double a, double b) {
  if (a < b) {
    return a;
  }
  return b;
}

CompositeShape::CompositeShape()
    : MaxShape(10), size_(0), array_(new Shape *[size_]) {}

CompositeShape::CompositeShape(const CompositeShape &other)
    : MaxShape(other.MaxShape), size_(other.size_), array_(new Shape *[size_]) {
  for (std::size_t i = 0; i < size_; ++i) {
    array_[i] = other.array_[i];
  }
}

CompositeShape::CompositeShape(CompositeShape &&other) noexcept
    : MaxShape(other.MaxShape), size_(other.size_), array_(other.array_) {
  other.size_ = 0;
  other.array_ = nullptr;
}

FrameRectangle CompositeShape::getFrameRectangle() {
  Point a(std::numeric_limits<double>::max(),
          std::numeric_limits<double>::max());
  Point b(std::numeric_limits<double>::max(),
          std::numeric_limits<double>::max());
  for (std::size_t i = 0; i < size_; ++i) {
    FrameRectangle temp = array_[i]->getFrameRectangle();
    Point temp_a(temp.pos_.GetX() - temp.WIDTH / 2,
                 temp.pos_.GetY() - temp.HEIGHT / 2);
    Point temp_b(temp.pos_.GetX() + temp.WIDTH / 2,
                 temp.pos_.GetY() + temp.HEIGHT / 2);
    a.SetX(min(a.GetX(), temp_a.GetX()));
    a.SetY(min(a.GetY(), temp_a.GetY()));
    b.SetX(min(b.GetX(), temp_b.GetX()));
    b.SetY(min(b.GetY(), temp_b.GetY()));
  }
  double width = b.GetX() - a.GetX();
  double height = b.GetY() - a.GetY();
  Point pos_((a.GetX() + b.GetX()) / 2, (a.GetY() + b.GetY()) / 2);
  return FrameRectangle(width, height, pos_);
}

void CompositeShape::push_back(Shape &data) {
  if (size_ + 1 > MaxShape) {
    throw std::out_of_range("Composite shape is full");
  }
  Shape **temp = new Shape *[size_ + 1];
  for (std::size_t i = 0; i < size_; ++i) {
    temp[i] = array_[i];
  }
  temp[size_] = &data;
  delete[] array_;
  array_ = temp;
  ++size_;
}

void CompositeShape::move(const double k) {
  for (std::size_t i = 0; i < size_; ++i) {
    array_[i]->move(k);
  }
}

void CompositeShape::scale(const double k) {
  FrameRectangle temp =
      getFrameRectangle(); // получаю общий ограничивающий прямоугольник
  Point temp_pos;
  for (std::size_t i = 0; i < size_; ++i) {
    temp_pos = array_[i]->getFrameRectangle().pos_; // сохраняю координаты
    // изначальные координаты фигуры
    // двигаю фигуру в центр общего ограничивающего прямоугольника,
    // чтобы он масштабировался относительно общего центра
    array_[i]->move(
        temp.pos_.GetX() - array_[i]->getFrameRectangle().pos_.GetX(),
        temp.pos_.GetY() * k - array_[i]->getFrameRectangle().pos_.GetY());
    array_[i]->scale(k); // масштабирую
    array_[i]->move(-temp_pos.GetX() * k,
                    -temp_pos.GetY() *
                        k); // вычитаю изначальные
                            // масштабированные координаты для сохранения
                            // расположения фигуры на составной фигуре
  }
}
Shape *CompositeShape::operator[](std::size_t index) {
  if (index >= size_) {
    throw std::out_of_range("Index greater than array size");
  }
  return array_[index];
}

std::size_t CompositeShape::size() const { return size_; }

void CompositeShape::swap(CompositeShape &other) {
  std::swap(size_, other.size_);
  std::swap(array_, other.array_);
}

CompositeShape &CompositeShape::operator=(const CompositeShape &other) {
  if (this != &other) {
    CompositeShape temp(other);
    swap(temp);
  }
  return *this;
}
