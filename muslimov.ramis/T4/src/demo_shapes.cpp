#include "../include/demo_shapes.hpp"
#include "../include/rectangle.hpp"
#include "../include/ellipse.hpp"
#include "../include/compositeShape.hpp"
#include "../include/shapePrinter.hpp"
#include <memory>

ShapesContainer createDemoContainer() {
    ShapesContainer c;
    c.add(std::make_unique<Rectangle>(Point{0.0, 0.0}, Point{4.0, 3.0}));
    c.add(std::make_unique<Ellipse>(Point{6.0, 2.0}, 1.5, 1.0));
    c.add(std::make_unique<Rectangle>(Point{-3.0, -1.0}, Point{-1.0, 1.0}));
    c.add(std::make_unique<Ellipse>(Point{2.0, -2.0}, 0.5, 0.5));

    auto comp = std::make_unique<CompositeShape>();
    comp->add(std::make_unique<Rectangle>(Point{10.0, 10.0}, Point{12.0, 11.0}));
    comp->add(std::make_unique<Ellipse>(Point{13.0, 10.5}, 0.8, 0.6));
    c.add(std::move(comp));

    return c;
}

void printDemo(std::ostream &os, const ShapesContainer &container) {
    const auto &items = container.components();
    for (const auto &p : items) {
        shapes_ui::printAny(os, *p);
    }
}
