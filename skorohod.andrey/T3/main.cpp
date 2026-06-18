#include "utils.hpp"
#include "geometry.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
#include <functional>
#include <iomanip>
#include <cctype>
#include <map>

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <filename>\n";
        return 1;
    }
    std::vector<Polygon> polygons;
    try
    {
        polygons = readPolygons(argv[1]);
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }
    using namespace std::placeholders;
    std::map<std::string, std::function<void(std::istream&, std::ostream&)>> commandMap;

    commandMap["AREA"] = std::bind(cmdArea, std::cref(polygons), _1, _2);
    commandMap["MAX"]  = std::bind(cmdMax,  std::cref(polygons), _1, _2);
    commandMap["MIN"]  = std::bind(cmdMin,  std::cref(polygons), _1, _2);
    commandMap["COUNT"]= std::bind(cmdCount,std::cref(polygons), _1, _2);
    commandMap["RIGHTSHAPES"] = std::bind(cmdRightshapes, std::cref(polygons), _1, _2);
    commandMap["ECHO"] = std::bind(cmdEcho, std::ref(polygons), _1, _2);

    std::string line;
    while (std::getline(std::cin, line))
    {
        if (line.empty()) continue;
        std::istringstream iss(line);
        std::string cmd;
        iss >> cmd;
        if (cmd.empty()) continue;
        auto it = commandMap.find(cmd);
        if (it != commandMap.end())
        {
            it->second(iss, std::cout);
        }
        else
        {
            std::cout << "<INVALID COMMAND>\n";
        }
    }

    return 0;
}
