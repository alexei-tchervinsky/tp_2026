#include <iostream>
#include <iomanip>
#include <vector>
#include <numeric>
#include <limits>

#include "polygon.hpp"
#include "utils.hpp"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Error: filename is not provided" << std::endl;
        return 1;
    };

    auto polygons = Utils::load_from_file(argv[1]);
    Utils::setup_iomanip(std::cout);

    std::string command;
    while (std::cin >> command) {
        try {
            if (command == "AREA") {
                std::string sub;
                if (!(std::cin >> sub)) {
                    throw std::invalid_argument("");
                }

                if (sub == "EVEN") {
                    std::cout << Utils::cmd_AREA_EVEN_ODD(polygons, false) << std::endl;
                } else if (sub == "ODD") {
                    std::cout << Utils::cmd_AREA_EVEN_ODD(polygons, true) << std::endl;
                } else if (sub == "MEAN") {
                    std::cout << Utils::cmd_AREA_MEAN(polygons) << std::endl;
                } else if (std::isdigit(sub[0])) {
                    std::size_t num = std::stoul(sub);
                    std::cout << Utils::cmd_AREA_NUM(polygons, num) << std::endl;
                } else {
                    throw std::invalid_argument("");
                }
            } else if (command == "MAX") {
                std::string sub;
                std::cin >> sub;
                if (sub == "AREA") std::cout << Utils::cmd_MAX_AREA(polygons) << std::endl;
                else if (sub == "VERTEXES") std::cout << Utils::cmd_MAX_VERTEXES(polygons) << std::endl;
                else throw std::invalid_argument("");
            } else if (command == "MIN") {
                std::string sub;
                std::cin >> sub;
                if (sub == "AREA") std::cout << Utils::cmd_MIN_AREA(polygons) << std::endl;
                else if (sub == "VERTEXES") std::cout << Utils::cmd_MIN_VERTEXES(polygons) << std::endl;
                else throw std::invalid_argument("");
            } else if (command == "COUNT") {
                std::string sub;
                if (!(std::cin >> sub)) {
                    throw std::invalid_argument("");
                }

                if (sub == "EVEN") {
                    std::cout << Utils::cmd_COUNT_EVEN_ODD(polygons, false) << std::endl;
                } else if (sub == "ODD") {
                    std::cout << Utils::cmd_COUNT_EVEN_ODD(polygons, true) << std::endl;
                } else if (std::isdigit(sub[0])) {
                    std::size_t num = std::stoul(sub);
                    std::cout << Utils::cmd_COUNT_NUM(polygons, num) << std::endl;
                } else {
                    throw std::invalid_argument("");
                }
            } else if (command == "ECHO") {
                Polygon p;
                std::cin >> p;
                std::cout << Utils::cmd_ECHO_POLYGON(polygons, p) << std::endl;
            } else if (command == "INFRAME") {
                Polygon p;
                std::cin >> p;
                std::cout << (Utils::cmd_INFRAME_POLYGON(polygons, p) ? "<TRUE>" : "<FALSE>") << std::endl;
            } else {
                throw std::runtime_error("Unknown command");
            }
        } catch (...) {
            std::cout << "<INVALID COMMAND>" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    return 0;
}
