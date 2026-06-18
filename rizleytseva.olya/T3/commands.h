#ifndef COMMANDS_H
#define COMMANDS_H

#include "polygon.h"
#include <vector>
#include <iostream>
#include <string>
#include <stdexcept>

void cmdArea(std::istream& is, std::ostream& os);
void cmdMax(std::istream& is, std::ostream& os);
void cmdMin(std::istream& is, std::ostream& os);
void cmdCount(std::istream& is, std::ostream& os);
void cmdLessArea(std::istream& is, std::ostream& os);
void cmdIntersections(std::istream& is, std::ostream& os);
void cmdMaxSeq(std::istream& is, std::ostream& os);

void setPolygons(const std::vector< Polygon >& polys);

// doTasks читает команды из std::cin до EOF
void doTasks(const std::vector< Polygon >& polys);

#endif // COMMANDS_H

