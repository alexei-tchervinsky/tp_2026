#include "polygon.hpp"
#include "commands.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <set>

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cerr << "Error: filename required" << std::endl;
        return 1;
    }

    std::ifstream file(argv[1]);
    if (!file)
    {
        std::cerr << "Error: cannot open file " << argv[1] << std::endl;
        return 1;
    }

    std::vector<tchervinsky::Polygon> polygons;
    std::string line;

    while (std::getline(file, line))
    {
        if (line.empty()) continue;

        std::istringstream iss(line);
        tchervinsky::Polygon p;

        if (!(iss >> p)) continue;

        // Must have at least 3 vertices
        if (p.points.size() < 3) continue;

        // No duplicate points
        std::set<tchervinsky::Point> uniq(p.points.begin(), p.points.end());
        if (uniq.size() != p.points.size()) continue;

        // No trailing garbage on the line
        std::string rest;
        std::getline(iss, rest);
        bool hasGarbage = false;
        for (char c : rest)
            if (c != ' ' && c != '\t' && c != '\r' && c != '\n')
            {
                hasGarbage = true; break;
            }
        if (hasGarbage) continue;

        polygons.push_back(p);
    }

    while (std::getline(std::cin, line))
    {
        if (line.empty()) continue;
        tchervinsky::processCommand(polygons, line);
    }

    return 0;
}

