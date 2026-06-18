#include "Polygon.hpp"
#include "Commands.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <algorithm>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Error: Provide exactly one argument (filename).\n";
        return 1;
    }

    std::ifstream file(argv[1]);
    if (!file.is_open()) {
        std::cerr << "Error: Cannot open file " << argv[1] << "\n";
        return 1;
    }

    std::vector<Polygon> polygons;

    while (!file.eof()) {
        Polygon p;
        if (file >> p) {
            polygons.push_back(p);
        } else {
            if (file.eof()) break;
            file.clear();
            std::string skip;
            file >> skip;
        }
    }

    file.close();

    doTasks(polygons);

    return 0;
}
