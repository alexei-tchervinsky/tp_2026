#include <iostream>
#include <iomanip>
#include <vector>
#include <numeric>
#include <limits>
#include <algorithm>
#include <cctype>
#include <map>
#include <functional>
#include <string>

#include "polygon.hpp"
#include "utils.hpp"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Error: filename is not provided" << std::endl;
        return 1;
    };

    auto polygons = Utils::load_from_file(argv[1]);
    Utils::setup_iomanip(std::cout);

    std::map<std::string, std::function<void()>> cmds;

    // using std::cref when function does not modify data
    //   and std::ref when it does
    // just passing polygons without std::(c)ref would show only initial data
    //   that were taken from file and would not reflect changes made by
    //   ECHO command
    cmds["MAX"] = std::bind(Utils::cmd_MAX, std::cref(polygons), std::ref(std::cin), std::ref(std::cout));
    cmds["MIN"] = std::bind(Utils::cmd_MIN, std::cref(polygons), std::ref(std::cin), std::ref(std::cout));
    cmds["AREA"] = std::bind(Utils::cmd_AREA, std::cref(polygons), std::ref(std::cin), std::ref(std::cout));
    cmds["COUNT"] = std::bind(Utils::cmd_COUNT, std::cref(polygons), std::ref(std::cin), std::ref(std::cout));
    cmds["ECHO"] = std::bind(Utils::cmd_ECHO, std::ref(polygons), std::ref(std::cin), std::ref(std::cout));
    cmds["INFRAME"] = std::bind(Utils::cmd_INFRAME, std::ref(polygons), std::ref(std::cin), std::ref(std::cout));

    std::string command;
    while (!(std::cin >> command).eof()) {
        try {
            cmds.at(command)();
        } catch (std::exception &e) {
            std::cout << "<INVALID COMMAND>" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    return 0;
}
