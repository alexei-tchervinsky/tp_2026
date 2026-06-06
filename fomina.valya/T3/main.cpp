#include "shapes.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <numeric>
#include <iomanip>
#include <iterator>
#include <climits>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>\n";
        return 1;
    }

    std::ifstream file(argv[1]);
    if (!file) {
        std::cerr << "Error: cannot open file " << argv[1] << "\n";
        return 1;
    }

    std::vector<Polygon> polygons;
    std::copy(std::istream_iterator<Polygon>(file), std::istream_iterator<Polygon>(), std::back_inserter(polygons));
    file.close();

    std::cout << std::fixed << std::setprecision(1);

    std::string line;
    while (std::getline(std::cin, line)) {
        if (line.empty()) continue;
        std::istringstream iss(line);
        std::string cmd;
        iss >> cmd;

        if (cmd == "AREA") {
            std::string sub;
            iss >> sub;
            if (sub == "EVEN") {
                double sum = std::accumulate(polygons.begin(), polygons.end(), 0.0,
                                             [](double acc, const Polygon& p) { return p.points.size() % 2 == 0 ? acc + area(p) : acc; });
                std::cout << sum << "\n";
            } else if (sub == "ODD") {
                double sum = std::accumulate(polygons.begin(), polygons.end(), 0.0,
                                             [](double acc, const Polygon& p) { return p.points.size() % 2 != 0 ? acc + area(p) : acc; });
                std::cout << sum << "\n";
            } else if (sub == "MEAN") {
                if (polygons.empty()) {
                    std::cout << "<INVALID COMMAND>\n";
                } else {
                    double sum = std::accumulate(polygons.begin(), polygons.end(), 0.0,
                                                 [](double acc, const Polygon& p) { return acc + area(p); });
                    std::cout << sum / polygons.size() << "\n";
                }
            } else {
                try {
                    int n = std::stoi(sub);
                    double sum = std::accumulate(polygons.begin(), polygons.end(), 0.0,
                                                 [n](double acc, const Polygon& p) { return p.points.size() == static_cast<size_t>(n) ? acc + area(p) : acc; });
                    std::cout << sum << "\n";
                } catch (...) {
                    std::cout << "<INVALID COMMAND>\n";
                }
            }
        }
        else if (cmd == "MAX" || cmd == "MIN") {
            std::string sub;
            iss >> sub;
            if (polygons.empty()) {
                std::cout << "<INVALID COMMAND>\n";
                continue;
            }
            if (sub == "AREA") {
                auto cmp = [](const Polygon& a, const Polygon& b) { return area(a) < area(b); };
                auto it = (cmd == "MAX") ? std::max_element(polygons.begin(), polygons.end(), cmp)
                : std::min_element(polygons.begin(), polygons.end(), cmp);
                std::cout << area(*it) << "\n";
            } else if (sub == "VERTEXES") {
                auto cmp = [](const Polygon& a, const Polygon& b) { return a.points.size() < b.points.size(); };
                auto it = (cmd == "MAX") ? std::max_element(polygons.begin(), polygons.end(), cmp)
                : std::min_element(polygons.begin(), polygons.end(), cmp);
                std::cout << static_cast<double>(it->points.size()) << "\n";
            } else {
                std::cout << "<INVALID COMMAND>\n";
            }
        }
        else if (cmd == "COUNT") {
            std::string sub;
            iss >> sub;
            if (sub == "EVEN") {
                std::cout << std::count_if(polygons.begin(), polygons.end(),
                                           [](const Polygon& p) { return p.points.size() % 2 == 0; }) << "\n";
            } else if (sub == "ODD") {
                std::cout << std::count_if(polygons.begin(), polygons.end(),
                                           [](const Polygon& p) { return p.points.size() % 2 != 0; }) << "\n";
            } else {
                try {
                    int n = std::stoi(sub);
                    std::cout << std::count_if(polygons.begin(), polygons.end(),
                                               [n](const Polygon& p) { return p.points.size() == static_cast<size_t>(n); }) << "\n";
                } catch (...) {
                    std::cout << "<INVALID COMMAND>\n";
                }
            }
        }
        else if (cmd == "RMECHO") {
            Polygon target;
            std::string target_str;
            std::getline(iss >> std::ws, target_str);

            std::istringstream target_iss(target_str);
            if (!(target_iss >> target)) {
                std::cout << "<INVALID COMMAND>\n";
                continue;
            }

            auto new_end = std::unique(polygons.begin(), polygons.end(),
                                       [&](const Polygon& a, const Polygon& b) { return a == target && b == target; });
            int removed = std::distance(new_end, polygons.end());
            polygons.erase(new_end, polygons.end());
            std::cout << removed << "\n";
        }
        else if (cmd == "INFRAME") {
            Polygon target;
            std::string target_str;
            std::getline(iss >> std::ws, target_str);

            std::istringstream target_iss(target_str);
            if (!(target_iss >> target) || target.points.empty()) {
                std::cout << "<INVALID COMMAND>\n";
                continue;
            }

            if (polygons.empty()) {
                std::cout << "<FALSE>\n";
                continue;
            }

            auto all_points = std::accumulate(polygons.begin(), polygons.end(), std::vector<Point>{},
                                              [](std::vector<Point> acc, const Polygon& p) {
                                                  acc.insert(acc.end(), p.points.begin(), p.points.end());
                                                  return acc;
                                              });

            auto minmax_x = std::minmax_element(all_points.begin(), all_points.end(),
                                                [](const Point& a, const Point& b) { return a.x < b.x; });
            auto minmax_y = std::minmax_element(all_points.begin(), all_points.end(),
                                                [](const Point& a, const Point& b) { return a.y < b.y; });

            auto t_minmax_x = std::minmax_element(target.points.begin(), target.points.end(),
                                                  [](const Point& a, const Point& b) { return a.x < b.x; });
            auto t_minmax_y = std::minmax_element(target.points.begin(), target.points.end(),
                                                  [](const Point& a, const Point& b) { return a.y < b.y; });

            bool inside = (t_minmax_x.first->x >= minmax_x.first->x) &&
            (t_minmax_x.second->x <= minmax_x.second->x) &&
            (t_minmax_y.first->y >= minmax_y.first->y) &&
            (t_minmax_y.second->y <= minmax_y.second->y);

            std::cout << (inside ? "<TRUE>" : "<FALSE>") << "\n";
        }
        else {
            std::cout << "<INVALID COMMAND>\n";
        }
    }

    return 0;
}
