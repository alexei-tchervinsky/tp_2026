#include "parsing.hpp"
#include <sstream>
#include <algorithm>
#include <vector>

bool parsePoint(const std::string& s, Point& pt)
{
    if (s.size() < 5 || s.front() != '(' || s.back() != ')') return false;
    std::string inner = s.substr(1, s.size() - 2);
    size_t semi = inner.find(';');
    if (semi == std::string::npos || semi == 0 || semi == inner.size() - 1)
    {
        return false;
    }

    auto check_digits = [](const std::string& str) {
        if (str.empty()) return false;
        size_t start = (str[0] == '-') ? 1 : 0;
        if (start == str.size()) return false;
        return std::all_of(str.begin() + start, str.end(), ::isdigit);
    };

    std::string x_str = inner.substr(0, semi);
    std::string y_str = inner.substr(semi + 1);

    if (!check_digits(x_str) || !check_digits(y_str)) return false;

    try {
        pt.x = std::stoi(x_str);
        pt.y = std::stoi(y_str);
    } catch (...) {
        return false;
    }
    return true;
}

bool parsePolygonLine(const std::string& line, Polygon& poly)
{
    if (line.empty()) return false;
    std::stringstream ss(line);
    size_t num_vertices;
    if (!(ss >> num_vertices)) return false;
    if (num_vertices < 3) return false;

    std::vector<std::string> tokens;
    std::string token;
    while (ss >> token) {
        tokens.push_back(token);
    }

    if (tokens.size() != num_vertices) return false;

    poly.points.resize(num_vertices);
    for (size_t i = 0; i < num_vertices; ++i) {
        if (!parsePoint(tokens[i], poly.points[i])) return false;
    }
    return true;
}

bool parsePolygonFromString(const std::string& str, Polygon& poly)
{
    std::stringstream ss(str);
    size_t num_vertices;
    if (!(ss >> num_vertices)) return false;
    if (num_vertices < 3) return false;

    poly.points.resize(num_vertices);
    for (size_t i = 0; i < num_vertices; ++i) {
        std::string token;
        if (!(ss >> token) || !parsePoint(token, poly.points[i])) return false;
    }

    std::string extra;
    if (ss >> extra) return false;

    return true;
}
