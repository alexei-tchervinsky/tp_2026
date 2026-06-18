#ifndef DEMO_SHAPES_HPP
#define DEMO_SHAPES_HPP

#include "../include/shapeContainer.hpp"
#include <ostream>

// Создаёт контейнер с демонстрационными фигурами (владеет фигурами)
ShapesContainer createDemoContainer();

// Печатает контейнер в заданный поток (использует shapePrinter)
void printDemo(std::ostream &os, const ShapesContainer &container);

#endif // DEMO_SHAPES_HPP
