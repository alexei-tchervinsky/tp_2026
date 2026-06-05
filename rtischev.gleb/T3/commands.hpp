#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <vector>
#include <iostream>
#include "polygon.hpp"

namespace Commands
{
    // Базовые команды
    void cmd_AREA(const std::vector<Polygon> &polygons, std::istream &in, std::ostream &out);
    void cmd_MAX(const std::vector<Polygon> &polygons, std::istream &in, std::ostream &out);
    void cmd_MIN(const std::vector<Polygon> &polygons, std::istream &in, std::ostream &out);
    void cmd_COUNT(const std::vector<Polygon> &polygons, std::istream &in, std::ostream &out);

    // Команды 2 вар
    void cmd_LESSAREA(const std::vector<Polygon> &polygons, std::istream &in, std::ostream &out);
    void cmd_MAXSEQ(const std::vector<Polygon> &polygons, std::istream &in, std::ostream &out);
}

#endif
