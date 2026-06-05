#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <functional>
#include <limits>
#include <algorithm>
#include <fstream>
#include <sstream>
#include "polygon.hpp"
#include "commands.hpp"

void load_from_file(const std::string &filename, std::vector<Polygon> &polygons)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Error: Could not open file." << std::endl;
        std::exit(1);
    }
    std::string line;
    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        Polygon poly;
        if (ss >> poly)
        {
            polygons.push_back(poly);
        }
    }
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cerr << "Error: filename is not provided" << std::endl;
        return 1;
    }

    std::vector<Polygon> polygons;
    load_from_file(argv[1], polygons);

    std::map<std::string, std::function<void(std::istream &)>> cmds;

    cmds["AREA"] = std::bind(Commands::cmd_AREA, std::cref(polygons), std::placeholders::_1, std::ref(std::cout));
    cmds["MAX"] = std::bind(Commands::cmd_MAX, std::cref(polygons), std::placeholders::_1, std::ref(std::cout));
    cmds["MIN"] = std::bind(Commands::cmd_MIN, std::cref(polygons), std::placeholders::_1, std::ref(std::cout));
    cmds["COUNT"] = std::bind(Commands::cmd_COUNT, std::cref(polygons), std::placeholders::_1, std::ref(std::cout));
    cmds["LESSAREA"] = std::bind(Commands::cmd_LESSAREA, std::cref(polygons), std::placeholders::_1, std::ref(std::cout));
    cmds["MAXSEQ"] = std::bind(Commands::cmd_MAXSEQ, std::cref(polygons), std::placeholders::_1, std::ref(std::cout));

    std::string line;
    while (std::getline(std::cin, line))
    {
        if (line.empty())
        {
            continue;
        }

        std::stringstream ss(line);
        std::string command;

        if (!(ss >> command))
        {
            continue;
        }

        try
        {
            cmds.at(command)(ss);

            std::string extra;
            if (ss >> extra)
            {
                throw std::runtime_error("Too many arguments");
            }
        }
        catch (const std::exception &e)
        {
            std::cout << "<INVALID COMMAND>\n";
        }
    }

    return 0;
}
