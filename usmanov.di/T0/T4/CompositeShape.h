#ifndef COMPOSITE_SHAPE_H
#define COMPOSITE_SHAPE_H
#include <vector>
#include <memory>
#include "shape.h"
#include "Rectangle.h"
#include "Circle.h"

class CompositeShape : public Shape
{
private:
    std::vector<std::unique_ptr<Shape>> shapes_;

    void addShapes() {}

    template<typename T, typename... Other>
    void addShapes(T&& first, Other&&... other)
    {
        shapes_.push_back(std::make_unique<std::remove_reference_t<T>>(
            std::forward<T>(first)));
        addShapes(std::forward<Other>(other)...);
    }

    void printInfo(std::ostream& out) const;
public:
    CompositeShape() = delete;

    template<typename... Shapes>
    CompositeShape(Shapes&&... args)
    {
        addShapes(std::forward<Shapes>(args)...);
    }

    CompositeShape(const CompositeShape&) = delete;
    CompositeShape(CompositeShape&&) = default;
    CompositeShape& operator=(const CompositeShape&) = delete;
    CompositeShape& operator=(CompositeShape&&) = default;

    virtual ~CompositeShape() = default;

    double getArea() const;
    Point getCenter()  const;
    void move(double xMove, double yMove);
    void scale(double scaleFactor);
    std::string getName() const { return std::string("COMPOSITE"); }

};
#endif /* COMPOSITE_SHAPE_H */
