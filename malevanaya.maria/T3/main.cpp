#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <functional>
#include <map>
#include <limits>
#include "polygon.hpp"
#include "utils.hpp"

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cerr << "Error: filename is not provided\n";
        return 1;
    }

    std::ifstream file(argv[1]);
    if (!file.is_open())
    {
        std::cerr << "Error: cannot open file '" << argv[1] << "'\n";
        return 1;
    }

    std::vector<Polygon> polygons;
    {
        std::string ln;
        while (std::getline(file, ln))
        {
            Polygon p;
            if (parseLine(ln, p) && p.points.size() >= 3)
                polygons.push_back(std::move(p));
        }
    }

    std::map< std::string, std::function< void() > > cmds;
    cmds["AREA"] = std::bind(cmd::AREA, std::cref(polygons), std::ref(std::cin), std::ref(std::cout));
    cmds["MAX"] = std::bind(cmd::MAX, std::cref(polygons), std::ref(std::cin), std::ref(std::cout));
    cmds["MIN"] = std::bind(cmd::MIN, std::cref(polygons), std::ref(std::cin), std::ref(std::cout));
    cmds["COUNT"] = std::bind(cmd::COUNT, std::cref(polygons), std::ref(std::cin), std::ref(std::cout));
    cmds["INFRAME"] = std::bind(cmd::INFRAME, std::cref(polygons), std::ref(std::cin), std::ref(std::cout));
    cmds["RIGHTSHAPES"] = std::bind(cmd::RIGHTSHAPES, std::cref(polygons), std::ref(std::cin), std::ref(std::cout));

    std::string command;
    while (!(std::cin >> command).eof())
    {
        try
        {
            cmds.at(command)();
        }
        catch (const std::exception&)
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
            std::cout << "<INVALID COMMAND>\n";
        }
    }

    return 0;
}
