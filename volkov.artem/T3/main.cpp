#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>

#include "geometry.hpp"
#include "commands.hpp"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Filename is not specified\n";
        return 1;
    }

    std::ifstream file(argv[1]);

    if (!file) {
        std::cerr << "File cannot be opened\n";
        return 1;
    }

    std::vector<Polygon> polygons;
    std::string line;

    while (std::getline(file, line)) {
        Polygon polygon;

        if (readPolygonFromLine(line, polygon)) {
            polygons.push_back(polygon);
        }
    }

    std::cout << std::fixed << std::setprecision(1);

    while (std::getline(std::cin, line)) {
        handleCommand(polygons, line);
    }

    return 0;
}
