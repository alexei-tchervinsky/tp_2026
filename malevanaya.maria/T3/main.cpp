#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

#include "polygon.hpp"
#include "utils.hpp"
void run_test();
int main(int argc, char* argv[])
{
    run_test();
    if (argc < 2)
    {
        std::cerr << "Error: no filename provided\n";
        return 1;
    }

    std::ifstream file(argv[1]);
    if (!file.is_open())
    {
        std::cerr << "Error: cannot open file '" << argv[1] << "'\n";
        return 1;
    }

    std::vector<std::string> lines;
    {
        std::string ln;
        while (std::getline(file, ln))
            lines.push_back(std::move(ln));
    }
    file.close();

    std::vector<Polygon> polygons;
    polygons.reserve(lines.size());
    std::transform(lines.begin(), lines.end(), std::back_inserter(polygons),
        [](const std::string& s) -> Polygon
        {
            Polygon p;
            parseLine(s, p);
            return p;
        });
    polygons.erase(
        std::remove_if(polygons.begin(), polygons.end(),
            [](const Polygon& p) { return p.points.size() < 3; }),
        polygons.end());

    std::string cmd;
    while (std::cin >> cmd)
    {
        if (cmd == "AREA")
        {
            std::string param;
            if (!(std::cin >> param)) { std::cout << "<INVALID COMMAND>\n"; continue; }
            cmdArea(polygons, param);
        }
        else if (cmd == "MAX")
        {
            std::string param;
            if (!(std::cin >> param)) { std::cout << "<INVALID COMMAND>\n"; continue; }
            cmdMax(polygons, param);
        }
        else if (cmd == "MIN")
        {
            std::string param;
            if (!(std::cin >> param)) { std::cout << "<INVALID COMMAND>\n"; continue; }
            cmdMin(polygons, param);
        }
        else if (cmd == "COUNT")
        {
            std::string param;
            if (!(std::cin >> param)) { std::cout << "<INVALID COMMAND>\n"; continue; }
            cmdCount(polygons, param);
        }
        else if (cmd == "INFRAME")
        {
            std::string rest;
            std::getline(std::cin, rest);
            std::istringstream iss(rest);
            Polygon poly;
            if (!parsePolygonArg(iss, poly)) { std::cout << "<INVALID COMMAND>\n"; continue; }
            cmdInframe(polygons, poly);
        }
        else if (cmd == "RIGHTSHAPES")
        {
            cmdRightshapes(polygons);
        }
        else
        {
            std::string rest;
            std::getline(std::cin, rest);
            std::cout << "<INVALID COMMAND>\n";
        }
    }
    return 0;
}
