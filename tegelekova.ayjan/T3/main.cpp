#include "polygon.hpp"
#include "commands.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

namespace tchervinsky
{
    void processCommand(std::vector<Polygon>& polygons, const std::string& line);
}

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cerr << "Ошибка: не указан файл с фигурами" << std::endl;
        return 1;
    }

    std::ifstream file(argv[1]);
    if (!file)
    {
        std::cerr << "Ошибка: не удалось открыть файл " << argv[1] << std::endl;
        return 1;
    }

    std::vector<tchervinsky::Polygon> polygons;
    std::string line;

    while (std::getline(file, line))
    {
        if (line.empty()) continue;

        std::istringstream iss(line);
        tchervinsky::Polygon p;

        if (iss >> p)
        {
            polygons.push_back(p);
        }
        // если ошибка — просто пропускаем строку
    }

    while (std::getline(std::cin, line))
    {
        if (line.empty()) continue;
        tchervinsky::processCommand(polygons, line);
    }

    return 0;
}
