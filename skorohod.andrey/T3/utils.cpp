#include "utils.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <numeric>
#include <functional>
#include <iomanip>
#include <cstdlib>
#include <cstddef>

std::vector<Polygon> readPolygons(const std::string& filename)
{
    std::vector<Polygon> polygons;
    std::ifstream file(filename);
    if (!file.is_open())
    {
        throw std::runtime_error("Cannot open file");
    }
    std::string line;
    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        Polygon poly;
        if (parsePolygon(iss, poly))
        {
            polygons.push_back(std::move(poly));
        }
    }
    return polygons;
}

bool parsePolygon(std::istream& is, Polygon& out)
{
    int vertexCount;
    if (!(is >> vertexCount)) return false;
    if(vertexCount < 3) return false;
    Polygon poly;
    for (int i = 0; i < vertexCount; ++i)
    {
        char open, semi, close;
        int x, y;
        if (!(is >> open >> x >> semi >> y >> close) ||
            open != '(' || semi != ';' || close != ')') {
            return false;
        }
        poly.points.push_back({x, y});
    }
    is >> std::ws;
    if (is.peek() != EOF || poly.points.size() != static_cast<std::size_t>(vertexCount)) return false;
    out = std::move(poly);
    return true;
}

bool isUnsignedNumber(const std::string &value)
{
    if (value.empty()) return false;
    for (char c : value)
    {
        if (!std::isdigit(c)) return false;
    }
    return true;
}

double areaEvenOdd(const std::vector<Polygon>& data, bool odd)
{
    return std::accumulate(data.begin(), data.end(), 0.0,
        [odd](double sum, const Polygon& p)
        {
            return sum + ((p.vertexCount() % 2 == (odd ? 1 : 0)) ? p.area() : 0.0);
        });
}

double areaMean(const std::vector<Polygon>& data)
{
    if (data.empty()) return 0.0;
    double total = std::accumulate(data.begin(), data.end(), 0.0,
        [](double s, const Polygon& p) { return s + p.area(); });
    return total / data.size();
}

double areaNum(const std::vector<Polygon>& data, std::size_t num_of_vertexes)
{
    return std::accumulate(data.begin(), data.end(), 0.0,
        [num_of_vertexes](double s, const Polygon& p)
        {
            return s + (p.vertexCount() == num_of_vertexes ? p.area() : 0.0);
        });
}

double maxArea(const std::vector<Polygon>& data)
{
    auto it = std::max_element(data.begin(), data.end(),
        [](const Polygon& a, const Polygon& b) { return a.area() < b.area(); });
    return (it != data.end()) ? it->area() : 0.0;
}

double minArea(const std::vector<Polygon>& data)
{
    auto it = std::min_element(data.begin(), data.end(),
        [](const Polygon& a, const Polygon& b) { return a.area() < b.area(); });
    return (it != data.end()) ? it->area() : 0.0;
}

std::size_t maxVertexes(const std::vector<Polygon>& data)
{
    auto it = std::max_element(data.begin(), data.end(),
        [](const Polygon& a, const Polygon& b) { return a.vertexCount() < b.vertexCount(); });
    return (it != data.end()) ? it->vertexCount() : 0;
}

std::size_t minVertexes(const std::vector<Polygon>& data)
{
    auto it = std::min_element(data.begin(), data.end(),
        [](const Polygon& a, const Polygon& b) { return a.vertexCount() < b.vertexCount(); });
    return (it != data.end()) ? it->vertexCount() : 0;
}

std::size_t countEvenOdd(const std::vector<Polygon>& data, bool odd)
{
    return std::count_if(data.begin(), data.end(),
        [odd](const Polygon& p) { return (p.vertexCount() % 2) == (odd ? 1 : 0); });
}

std::size_t countNum(const std::vector<Polygon>& data, std::size_t num_of_vertexes)
{
    return std::count_if(data.begin(), data.end(),
        [num_of_vertexes](const Polygon& p) { return p.vertexCount() == num_of_vertexes; });
}

void setupIomanip(std::ostream &os)
{
    os << std::fixed << std::setprecision(1);
}

void cmdArea(const std::vector<Polygon>& data, std::istream& is, std::ostream& os)
{
    std::string param;
    is >> param;
    if (param.empty()) {
        os << "<INVALID COMMAND>\n";
        return;
    }
    if (param == "EVEN") {
        setupIomanip(os);
        os << areaEvenOdd(data, false) << '\n';
    } else if (param == "ODD") {
        setupIomanip(os);
        os << areaEvenOdd(data, true) << '\n';
    } else if (param == "MEAN") {
        if (data.empty()) {
            os << "<INVALID COMMAND>\n";
            return;
        }
        setupIomanip(os);
        os << areaMean(data) << '\n';
    } else if (isUnsignedNumber(param) && std::stoul(param) >= 3) {
        std::size_t num = std::stoul(param);
        setupIomanip(os);
        os << areaNum(data, num) << '\n';
    } else {
        os << "<INVALID COMMAND>\n";
    }
}

void cmdMax(const std::vector<Polygon>& data, std::istream& is, std::ostream& os)
{
    std::string sub;
    is >> sub;
    if (sub.empty() || data.empty()) {
        os << "<INVALID COMMAND>\n";
        return;
    }
    if (sub == "AREA") {
        setupIomanip(os);
        os << maxArea(data) << '\n';
    } else if (sub == "VERTEXES") {
        os << maxVertexes(data) << '\n';
    } else {
        os << "<INVALID COMMAND>\n";
    }
}

void cmdMin(const std::vector<Polygon>& data, std::istream& is, std::ostream& os)
{
    std::string sub;
    is >> sub;
    if (sub.empty() || data.empty()) {
        os << "<INVALID COMMAND>\n";
        return;
    }
    if (sub == "AREA") {
        setupIomanip(os);
        os << minArea(data) << '\n';
    } else if (sub == "VERTEXES") {
        os << minVertexes(data) << '\n';
    } else {
        os << "<INVALID COMMAND>\n";
    }
}

void cmdCount(const std::vector<Polygon>& data, std::istream& is, std::ostream& os)
{
    std::string param;
    is >> param;
    if (param.empty()) {
        os << "<INVALID COMMAND>\n";
        return;
    }
    if (param == "EVEN") {
        os << countEvenOdd(data, false) << '\n';
    } else if (param == "ODD") {
        os << countEvenOdd(data, true) << '\n';
    } else if (isUnsignedNumber(param) && std::stoul(param) >= 3) {
        std::size_t num = std::stoul(param);
        os << countNum(data, num) << '\n';
    } else {
        os << "<INVALID COMMAND>\n";
    }
}

void cmdEcho(std::vector<Polygon>& data, std::istream& is, std::ostream& os)
{
    Polygon pattern;
    if (!parsePolygon(is, pattern))
    {
        os << "<INVALID COMMAND>\n";
        return;
    }
    std::string leftover;
    if (is >> leftover)
    {
        os << "<INVALID COMMAND>\n";
        return;
    }
    std::vector<Polygon> newData;
    newData = std::accumulate(data.begin(), data.end(), std::vector<Polygon>(),
        [&pattern](std::vector<Polygon> acc, const Polygon& p) {
            acc.push_back(p);
            if (p == pattern)
            {
                acc.push_back(p);
            }
            return acc;
        });
    std::size_t added = newData.size() - data.size();
    data = std::move(newData);
    if (added == 0) os << "<INVALID COMMAND>\n";
    else os << added << '\n';
}

void cmdRightshapes(const std::vector<Polygon>& data, std::istream& is, std::ostream& os)
{
    std::string extra;
    if (is >> extra)
    {
        os << "<INVALID COMMAND>\n";
        return;
    }
    std::size_t count = std::count_if(data.begin(), data.end(),
        [](const Polygon& p) { return p.hasRightAngle(); });
    os << count << '\n';
}
