#ifndef COMMANDS_H
#define COMMANDS_H

#include <vector>
#include <sstream>
#include "Polygon.h"

void cmdArea(const std::vector<Polygon>& figures, std::stringstream& ss);
void cmdMax(const std::vector<Polygon>& figures, std::stringstream& ss);
void cmdMin(const std::vector<Polygon>& figures, std::stringstream& ss);
void cmdCount(const std::vector<Polygon>& figures, std::stringstream& ss);
void cmdIntersections(const std::vector<Polygon>& figures, std::stringstream& ss);
void cmdRmEcho(std::vector<Polygon>& figures, std::stringstream& ss);

#endif
