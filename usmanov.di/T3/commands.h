#ifndef COMMANDS_H
#define COMMANDS_H
#include "Polygon.h"
#include <iostream>
#include <vector>
#include <sstream>

void cPrintDouble(double value);

void cArea(std::istringstream& iss, const std::vector<Polygon>& polygons);
void cMax(std::istringstream& iss, const std::vector<Polygon>& polygons);
void cMin(std::istringstream& iss, const std::vector<Polygon>& polygons);
void cCount(std::istringstream& iss, const std::vector<Polygon>& polygons);
void cRMEcho(std::istringstream& iss, std::vector<Polygon>& polygons);
void cInFrame(std::istringstream& iss, const std::vector<Polygon>& polygons);

#endif
