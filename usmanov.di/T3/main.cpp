#include "Polygon.h"
#include "commands.h"
#include "ioHandle.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iterator>
#include <limits>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Error: file is not open\n";
        return 1;
    }

    std::ifstream ifs;

    ifs.open(argv[1]);

    if (!ifs) {
        std::cerr << "Error: file is not open\n";
        return 1;
    }

    std::vector<Polygon> polygons;

    while (!ifs.eof()) {
        std::copy(
            std::istream_iterator<Polygon>(ifs),
            std::istream_iterator<Polygon>(),
            std::back_inserter(polygons)
        );

        if (!ifs.eof() && ifs.fail()) {
            ifs.clear();
            ifs.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    ifs.close();

    std::string line;

    while (std::getline(std::cin, line)) {
        if (line.empty()) {
            continue;
        }

        std::istringstream iss(line);
        std::string command;

        iss >> command;

        if (command == "AREA") {
            cArea(iss, polygons);
        }
        else if (command == "MAX") {
            cMax(iss, polygons);
        }
        else if (command == "MIN") {
            cMin(iss, polygons);
        }
        else if (command == "COUNT") {
            cCount(iss, polygons);
        }
        else if (command == "RMECHO") {
            cRMEcho(iss, polygons);
        }
        else if (command == "INFRAME") {
            cInFrame(iss, polygons);
        }
        else {
            std::cout << "<INVALID COMMAND>\n";
        }
    }

    return 0;
}
