#ifndef SHAPES_CONTAINER_HPP
#define SHAPES_CONTAINER_HPP

#include <vector>
#include <memory>
#include "shape.hpp"

class ShapesContainer {
public:
    using Container = std::vector<std::unique_ptr<Shape>>;

    ShapesContainer() = default;
    ShapesContainer(const ShapesContainer&) = delete;
    ShapesContainer& operator=(const ShapesContainer&) = delete;
    ShapesContainer(ShapesContainer&&) = default;
    ShapesContainer& operator=(ShapesContainer&&) = default;

    // Добавить фигуру (передаём владение)
    void add(std::unique_ptr<Shape> shape);

    // Количество фигур
    std::size_t size() const noexcept;

    // Массовые операции
    void scaleAll(double factor);
    void moveAll(double dx, double dy);

    // Доступ для чтения к компонентам (const)
    const Container& components() const noexcept { return shapes_; }

private:
    Container shapes_;
};

#endif // SHAPES_CONTAINER_HPP
