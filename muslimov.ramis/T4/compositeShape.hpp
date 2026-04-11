#ifndef COMPOSITE_SHAPE_HPP
#define COMPOSITE_SHAPE_HPP

#include "shape.hpp"
#include "point.hpp"
#include <vector>
#include <memory>
#include <string>

class CompositeShape : public Shape
{
public:
    CompositeShape() = default;
    ~CompositeShape() override = default;

    const std::vector<std::unique_ptr<Shape>>& components() const noexcept {
    return shapes_;
    }


    //Запрещаем копирование, разрешаем перемещение
    CompositeShape(const CompositeShape&) = delete;
    CompositeShape& operator=(const CompositeShape&) = delete;
    CompositeShape(CompositeShape&&) = default;
    CompositeShape& operator=(CompositeShape&&) = default;

    //Добавить фигуру (передаем владение)
    void add(std::unique_ptr<Shape> shape);

    //Количество фигур
    std::size_t size() const noexcept;

    //Shape interface
    double getArea() const override;
    Point getCenter() const override;
    void move(double dx, double dy) override;
    void scale(double factor) override;
    std::string getName() const override;

    //Получить bounding box композиции
    void getBoundingBox(double &left, double &bottom, double &right, double &top) const override;

private:
    std::vector<std::unique_ptr<Shape>> shapes_;
};


#endif //COMPOSITE_SHAPE_HPP
