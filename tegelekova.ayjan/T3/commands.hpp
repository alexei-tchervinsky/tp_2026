#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include "polygon.hpp"
#include <vector>
#include <string>

namespace tchervinsky
{
    void processCommand(std::vector<Polygon>& polygons, const std::string& line);
}

#endif
