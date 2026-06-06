#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Polygon.h"
#include "Commands.h"

int main(int argc, char* argv[]) {
    if (argc < 2) return 1;
    std::ifstream file(argv[1]); if (!file) return 1;
    std::vector<Polygon> figures; std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        std::stringstream ss(line); Polygon poly;
        if (ss >> poly) {
            std::string extra; if (!(ss >> extra)) figures.push_back(poly);
        }
    }
    while (std::getline(std::cin, line)) {
        if (line.empty()) continue;
        std::stringstream ss(line); std::string cmd;
        if (!(ss >> cmd)) continue;
        try {
            if (cmd == "AREA") cmdArea(figures, ss);
            else if (cmd == "INTERSECTIONS") cmdIntersections(figures, ss);
            else if (cmd == "RMECHO") cmdRmEcho(figures, ss);
            else if (cmd == "COUNT") cmdCount(figures, ss);
            else if (cmd == "MAX") cmdMax(figures, ss);
            else if (cmd == "MIN") cmdMin(figures, ss);
            else throw std::runtime_error("");
        } catch (...) { std::cout << "<INVALID COMMAND>\n"; }
    }
    return 0;
}
