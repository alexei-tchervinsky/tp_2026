#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <functional>

#include "geometry.hpp"
#include "parsing.hpp"
#include "commands.hpp"

int main(int argc, char* argv[])
{
    if (argc < 2) {
        std::cerr << "Error: File name is not provided.\n";
        return 1;
    }

    std::ifstream infile(argv[1]);
    if (!infile.is_open()) {
        std::cerr << "Error: Cannot open file " << argv[1] << "\n";
        return 1;
    }

    std::vector<Polygon> polygons;
    std::string line;
    while (std::getline(infile, line)) {
        Polygon poly;
        if (parsePolygonLine(line, poly)) {
            polygons.push_back(poly);
        }
    }
    infile.close();

    using CmdFunc = std::function<void(const std::vector<Polygon>&, std::istream&)>;
    std::map<std::string, CmdFunc> cmdMap;

    cmdMap["AREA"] = handleArea;
    cmdMap["MAX"] = handleMax;
    cmdMap["MIN"] = handleMin;
    cmdMap["COUNT"] = handleCount;
    cmdMap["RECTS"] = handleRects;
    cmdMap["INTERSECTIONS"] = handleIntersections;

    std::string command;
    while (std::cin >> command) {
        auto it = cmdMap.find(command);
        if (it != cmdMap.end()) {
            it->second(polygons, std::cin);
        } else {
            std::cout << "<INVALID COMMAND>\n";
            std::string dummy;
            std::getline(std::cin, dummy);
        }
    }

    return 0;
}
