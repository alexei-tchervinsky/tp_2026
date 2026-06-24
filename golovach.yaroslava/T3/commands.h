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

void cmdRmEcho(std::istream& is, std::ostream& os);
void cmdSame(std::istream& is, std::ostream& os);

void setPolygons(const std::vector< Polygon >& polys);
void doTasks(const std::vector< Polygon >& polys);

#endif // COMMANDS_H
