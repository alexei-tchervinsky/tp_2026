#include "commands.hpp"
#include "stream_guard.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>

namespace tchervinsky
{
    static void printDouble(double value)
    {
        StreamGuard guard(std::cout);
        std::cout << std::fixed << std::setprecision(1) << value << std::endl;
    }

    static bool hasDuplicatePoints(const Polygon& p)
    {
        const auto& points = p.points;
        for (size_t i = 0; i < points.size(); ++i)
            for (size_t j = i + 1; j < points.size(); ++j)
                if (points[i].x == points[j].x && points[i].y == points[j].y)
                    return true;
        return false;
    }

    void processCommand(std::vector<Polygon>& polygons, const std::string& line)
    {
        std::istringstream iss(line);
        std::string cmd;
        iss >> cmd;

        if (cmd == "AREA")
        {
            std::string param;
            iss >> param;

            if (param == "EVEN")
            {
                double sum = 0.0;
                for (size_t i = 0; i < polygons.size(); i++)
                    if (polygons[i].points.size() % 2 == 0)
                        sum += getArea(polygons[i]);
                printDouble(sum);
            }
            else if (param == "ODD")
            {
                double sum = 0.0;
                for (size_t i = 0; i < polygons.size(); i++)
                    if (polygons[i].points.size() % 2 == 1)
                        sum += getArea(polygons[i]);
                printDouble(sum);
            }
            else if (param == "MEAN")
            {
                if (polygons.empty())
                {
                    std::cout << "<INVALID COMMAND>" << std::endl;
                    return;
                }
                double sum = 0.0;
                for (size_t i = 0; i < polygons.size(); i++)
                    sum += getArea(polygons[i]);
                printDouble(sum / polygons.size());
            }
            else
            {
                size_t vertexCount;
                try {
                    vertexCount = std::stoul(param);
                }
                catch (...) {
                    std::cout << "<INVALID COMMAND>" << std::endl;
                    return;
                }
                if (vertexCount < 3)
                {
                    std::cout << "<INVALID COMMAND>" << std::endl;
                    return;
                }
                double sum = 0.0;
                for (size_t i = 0; i < polygons.size(); i++)
                    if (polygons[i].points.size() == vertexCount)
                        sum += getArea(polygons[i]);
                printDouble(sum);
            }
        }
        else if (cmd == "MAX")
        {
            std::string param;
            iss >> param;

            if (polygons.empty())
            {
                std::cout << "<INVALID COMMAND>" << std::endl;
                return;
            }

            if (param == "AREA")
            {
                double maxArea = getArea(polygons[0]);
                for (size_t i = 1; i < polygons.size(); i++)
                {
                    double area = getArea(polygons[i]);
                    if (area > maxArea) maxArea = area;
                }
                printDouble(maxArea);
            }
            else if (param == "VERTEXES")
            {
                size_t maxVert = polygons[0].points.size();
                for (size_t i = 1; i < polygons.size(); i++)
                    if (polygons[i].points.size() > maxVert)
                        maxVert = polygons[i].points.size();
                std::cout << maxVert << std::endl;
            }
            else
                std::cout << "<INVALID COMMAND>" << std::endl;
        }
        else if (cmd == "MIN")
        {
            std::string param;
            iss >> param;

            if (polygons.empty())
            {
                std::cout << "<INVALID COMMAND>" << std::endl;
                return;
            }

            if (param == "AREA")
            {
                double minArea = getArea(polygons[0]);
                for (size_t i = 1; i < polygons.size(); i++)
                {
                    double area = getArea(polygons[i]);
                    if (area < minArea) minArea = area;
                }
                printDouble(minArea);
            }
            else if (param == "VERTEXES")
            {
                size_t minVert = polygons[0].points.size();
                for (size_t i = 1; i < polygons.size(); i++)
                    if (polygons[i].points.size() < minVert)
                        minVert = polygons[i].points.size();
                std::cout << minVert << std::endl;
            }
            else
                std::cout << "<INVALID COMMAND>" << std::endl;
        }
        else if (cmd == "COUNT")
        {
            std::string param;
            iss >> param;

            if (param == "EVEN")
            {
                size_t count = 0;
                for (size_t i = 0; i < polygons.size(); i++)
                    if (polygons[i].points.size() % 2 == 0)
                        count++;
                std::cout << count << std::endl;
            }
            else if (param == "ODD")
            {
                size_t count = 0;
                for (size_t i = 0; i < polygons.size(); i++)
                    if (polygons[i].points.size() % 2 == 1)
                        count++;
                std::cout << count << std::endl;
            }
            else
            {
                size_t vertexCount;
                try {
                    vertexCount = std::stoul(param);
                }
                catch (...) {
                    std::cout << "<INVALID COMMAND>" << std::endl;
                    return;
                }
                if (vertexCount < 3)
                {
                    std::cout << "<INVALID COMMAND>" << std::endl;
                    return;
                }
                size_t count = 0;
                for (size_t i = 0; i < polygons.size(); i++)
                    if (polygons[i].points.size() == vertexCount)
                        count++;
                std::cout << count << std::endl;
            }
        }
        else if (cmd == "ECHO")
        {
            Polygon target;
            iss >> target;
            if (iss.fail() || target.points.empty())
            {
                std::cout << "<INVALID COMMAND>" << std::endl;
                return;
            }

            if (target.points.size() < 3)
            {
                std::cout << "<INVALID COMMAND>" << std::endl;
                return;
            }

            if (hasDuplicatePoints(target))
            {
                std::cout << "<INVALID COMMAND>" << std::endl;
                return;
            }

            size_t addedCount = 0;
            for (size_t i = 0; i < polygons.size(); i++)
            {
                if (polygons[i] == target)
                {
                    polygons.insert(polygons.begin() + i + 1, target);
                    addedCount++;
                    i++;
                }
            }
            std::cout << addedCount << std::endl;
        }
        else if (cmd == "INFRAME")
        {
            Polygon target;
            iss >> target;
            if (iss.fail() || target.points.empty())
            {
                std::cout << "<INVALID COMMAND>" << std::endl;
                return;
            }

            if (target.points.size() < 3)
            {
                std::cout << "<INVALID COMMAND>" << std::endl;
                return;
            }

            if (hasDuplicatePoints(target))
            {
                std::cout << "<INVALID COMMAND>" << std::endl;
                return;
            }

            if (polygons.empty())
            {
                std::cout << "<INVALID COMMAND>" << std::endl;
                return;
            }

            bool result = isInFrame(target, polygons);
            std::cout << (result ? "<TRUE>" : "<FALSE>") << std::endl;
        }
        else
        {
            std::cout << "<INVALID COMMAND>" << std::endl;
        }
    }
}
