#ifndef SHAPE_PRINTER_HPP
#define SHAPE_PRINTER_HPP

#include <ostream>
#include "shape.hpp"
#include "compositeShape.hpp"

namespace shapes_ui {
    // Печать простой фигуры в одну строку: [NAME, (x.xx, y.yy), area]
    void printSimple(std::ostream &os, const Shape &s);

    // Печать составной фигуры многострочно
    void printComposite(std::ostream &os, const CompositeShape &c);

    // Универсальная печать: определяет, составная ли фигура
    void printAny(std::ostream &os, const Shape &s);
}

#endif // SHAPE_PRINTER_HPP
