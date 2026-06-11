#include "shapes.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <climits>

bool isValidPolygon(const Polygon& p) {
    return p.points.size() >= 3;
}

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
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;

        std::istringstream iss(line);
        Polygon p;
        if (iss >> p && isValidPolygon(p)) {
            polygons.push_back(p);
        }
    }
    file.close();

    std::cout << std::fixed << std::setprecision(1);

    std::string cmd_line;
    while (std::getline(std::cin, cmd_line)) {
        if (cmd_line.empty()) continue;
        std::istringstream iss(cmd_line);
        std::string cmd;
        iss >> cmd;

        if (cmd == "AREA") {
            std::string sub;
            iss >> sub;

            if (sub == "EVEN") {
                double sum = 0.0;
                for (const auto& p : polygons) {
                    if (p.points.size() % 2 == 0) {
                        sum += area(p);
                    }
                }
                std::cout << sum << "\n";
            }
            else if (sub == "ODD") {
                double sum = 0.0;
                for (const auto& p : polygons) {
                    if (p.points.size() % 2 != 0) {
                        sum += area(p);
                    }
                }
                std::cout << sum << "\n";
            }
            else if (sub == "MEAN") {
                if (polygons.empty()) {
                    std::cout << "<INVALID COMMAND>\n";
                } else {
                    double sum = 0.0;
                    for (const auto& p : polygons) {
                        sum += area(p);
                    }
                    std::cout << sum / polygons.size() << "\n";
                }
            }
            else {
                try {
                    int n = std::stoi(sub);
                    if (n < 3) {
                        std::cout << "<INVALID COMMAND>\n";
                    } else {
                        double sum = 0.0;
                        for (const auto& p : polygons) {
                            if (p.points.size() == static_cast<size_t>(n)) {
                                sum += area(p);
                            }
                        }
                        std::cout << sum << "\n";
                    }
                } catch (...) {
                    std::cout << "<INVALID COMMAND>\n";
                }
            }
        }
        else if (cmd == "MAX" || cmd == "MIN") {
            if (polygons.empty()) {
                std::cout << "<INVALID COMMAND>\n";
                continue;
            }

            std::string sub;
            iss >> sub;

            if (sub == "AREA") {
                double best = area(polygons[0]);
                for (size_t i = 1; i < polygons.size(); ++i) {
                    double a = area(polygons[i]);
                    if (cmd == "MAX") {
                        if (a > best) best = a;
                    } else {
                        if (a < best) best = a;
                    }
                }
                std::cout << best << "\n";
            }
            else if (sub == "VERTEXES") {
                size_t best = polygons[0].points.size();
                for (size_t i = 1; i < polygons.size(); ++i) {
                    size_t v = polygons[i].points.size();
                    if (cmd == "MAX") {
                        if (v > best) best = v;
                    } else {
                        if (v < best) best = v;
                    }
                }
                std::cout << best << "\n";
            }
            else {
                std::cout << "<INVALID COMMAND>\n";
            }
        }
        else if (cmd == "COUNT") {
            std::string sub;
            iss >> sub;

            if (sub == "EVEN") {
                int cnt = 0;
                for (const auto& p : polygons) {
                    if (p.points.size() % 2 == 0) cnt++;
                }
                std::cout << cnt << "\n";
            }
            else if (sub == "ODD") {
                int cnt = 0;
                for (const auto& p : polygons) {
                    if (p.points.size() % 2 != 0) cnt++;
                }
                std::cout << cnt << "\n";
            }
            else {
                try {
                    int n = std::stoi(sub);
                    if (n < 3) {
                        std::cout << "<INVALID COMMAND>\n";
                    } else {
                        int cnt = 0;
                        for (const auto& p : polygons) {
                            if (p.points.size() == static_cast<size_t>(n)) cnt++;
                        }
                        std::cout << cnt << "\n";
                    }
                } catch (...) {
                    std::cout << "<INVALID COMMAND>\n";
                }
            }
        }
        else if (cmd == "RMECHO") {
            std::string rest;
            std::getline(iss >> std::ws, rest);

            std::istringstream target_iss(rest);
            Polygon target;
            if (!(target_iss >> target)) {
                std::cout << "<INVALID COMMAND>\n";
                continue;
            }

            int removed = 0;
            std::vector<Polygon> result;

            for (size_t i = 0; i < polygons.size(); ++i) {
                result.push_back(polygons[i]);
                if (i + 1 < polygons.size() && polygons[i] == target && polygons[i + 1] == target) {
                    result.pop_back();
                    removed++;
                }
            }

            polygons = std::move(result);
            std::cout << removed << "\n";
        }
        else if (cmd == "INFRAME") {
            std::string rest;
            std::getline(iss >> std::ws, rest);

            std::istringstream target_iss(rest);
            Polygon target;
            if (!(target_iss >> target)) {
                std::cout << "<INVALID COMMAND>\n";
                continue;
            }

            if (polygons.empty()) {
                std::cout << "<FALSE>\n";
                continue;
            }

            int global_min_x = INT_MAX, global_max_x = INT_MIN;
            int global_min_y = INT_MAX, global_max_y = INT_MIN;

            for (const auto& p : polygons) {
                for (const auto& pt : p.points) {
                    if (pt.x < global_min_x) global_min_x = pt.x;
                    if (pt.x > global_max_x) global_max_x = pt.x;
                    if (pt.y < global_min_y) global_min_y = pt.y;
                    if (pt.y > global_max_y) global_max_y = pt.y;
                }
            }

            int t_min_x = INT_MAX, t_max_x = INT_MIN;
            int t_min_y = INT_MAX, t_max_y = INT_MIN;

            for (const auto& pt : target.points) {
                if (pt.x < t_min_x) t_min_x = pt.x;
                if (pt.x > t_max_x) t_max_x = pt.x;
                if (pt.y < t_min_y) t_min_y = pt.y;
                if (pt.y > t_max_y) t_max_y = pt.y;
            }

            bool inside = (t_min_x >= global_min_x) &&
            (t_max_x <= global_max_x) &&
            (t_min_y >= global_min_y) &&
            (t_max_y <= global_max_y);

            std::cout << (inside ? "<TRUE>" : "<FALSE>") << "\n";
        }
        else {
            std::cout << "<INVALID COMMAND>\n";
        }
    }

    return 0;
}
