#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <functional>
#include "Polygon.h"
#include "Commands.h"

int main(int argc, char* argv[]) {
    if (argc < 2) return 1;
    std::ifstream file(argv[1]);
    if (!file) return 1;

    std::vector<Polygon> figures;
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        std::stringstream ss(line);
        Polygon poly;
        if (ss >> poly) {
            std::string extra;
            if (!(ss >> extra)) figures.push_back(poly);
        }
    }

    std::stringstream ss;
    std::map<std::string, std::function<void(void)>> cmds = {
        {"AREA", [&]() { cmdArea(figures, ss); }},
        {"MAX", [&]() { cmdMax(figures, ss); }},
        {"MIN", [&]() { cmdMin(figures, ss); }},
        {"COUNT", [&]() { cmdCount(figures, ss); }},
        {"INTERSECTIONS", [&]() { cmdIntersections(figures, ss); }},
        {"RMECHO", [&]() { cmdRmEcho(figures, ss); }}
    };

    while (std::getline(std::cin, line)) {
        if (line.empty()) continue;
        ss.clear();
        ss.str(line);
        std::string cmdName;
        if (!(ss >> cmdName)) continue;

        try {
            auto it = cmds.find(cmdName);
            if (it != cmds.end()) {
                it->second();
            } else {
                throw std::runtime_error("");
            }
        } catch (...) {
            std::cout << "<INVALID COMMAND>\n";
        }
    }

    return 0;
}
