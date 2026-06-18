#include "../include/shapePrinter.hpp"
#include <iomanip>

namespace shapes_ui {

void printSimple(std::ostream &os, const Shape &s) {
    Point c = s.getCenter();
    os << "[" << s.getName() << ", ("
       << std::fixed << std::setprecision(2) << c.x << ", " << c.y << "), "
       << std::fixed << std::setprecision(2) << s.getArea() << "]";
}

void printComposite(std::ostream &os, const CompositeShape &c) {
    Point cc = c.getCenter();
    os << "[" << c.getName() << ", ("
       << std::fixed << std::setprecision(2) << cc.x << ", " << cc.y << "), "
       << std::fixed << std::setprecision(2) << c.getArea() << ":\n";

    const auto &children = c.components();
    for (std::size_t i = 0; i < children.size(); ++i) {
        os << "  ";
        printSimple(os, *children[i]);
        if (i + 1 < children.size()) os << ",\n";
        else os << "\n";
    }
    os << "]\n";
}

void printAny(std::ostream &os, const Shape &s) {
    // Попытка dynamic_cast к CompositeShape
    if (const CompositeShape *c = dynamic_cast<const CompositeShape*>(&s)) {
        printComposite(os, *c);
    } else {
        printSimple(os, s);
        os << "\n";
    }
}

} // namespace shapes_ui
