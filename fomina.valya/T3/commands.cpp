#include "commands.hpp"
#include "geometry.hpp"
#include "iofmtguard.hpp"
#include <sstream>
#include <algorithm>
#include <numeric>
#include <iomanip>
#include <functional>
#include <map>
#include <string>
#include <iostream>

struct VertexCountFilter
{
    enum Type
    {
        EVEN,
        ODD,
        EXACT
    } type;
    size_t exact_count;

    VertexCountFilter(Type t, size_t exact = 0) : type(t), exact_count(exact) {}

    bool operator()(const Polygon &poly) const
    {
        if (type == EVEN)
            return poly.points.size() % 2 == 0;
        if (type == ODD)
            return poly.points.size() % 2 != 0;
        return poly.points.size() == exact_count;
    }
};

double addArea(double sum, const Polygon &p)
{
    return sum + getArea(p);
}

const std::map<std::string, VertexCountFilter::Type> filter_map = {
    {"EVEN", VertexCountFilter::EVEN},
    {"ODD", VertexCountFilter::ODD}};

    void handleArea(std::stringstream &ss, std::vector<Polygon> &shapes)
    {
        std::string sub;
        if (!(ss >> sub))
        {
            std::cout << "<INVALID COMMAND>\n";
            return;
        }

        using namespace std::placeholders;

        if (sub == "MEAN")
        {
            if (shapes.empty())
            {
                std::cout << "<INVALID COMMAND>\n";
                return;
            }
            double total_area = std::accumulate(shapes.begin(), shapes.end(), 0.0,
                                                std::bind(addArea, _1, _2));
            std::cout << std::fixed << std::setprecision(1) << total_area / shapes.size() << "\n";
        }
        else if (filter_map.count(sub))
        {
            VertexCountFilter filter(filter_map.at(sub));
            double total_area = std::accumulate(shapes.begin(), shapes.end(), 0.0,
                                                [&filter](double sum, const Polygon &p)
                                                { return sum + (filter(p) ? getArea(p) : 0.0); });
            std::cout << std::fixed << std::setprecision(1) << total_area << "\n";
        }
        else
        {
            try
            {
                size_t num = std::stoull(sub);
                if (num < 3)
                {
                    std::cout << "<INVALID COMMAND>\n";
                    return;
                }
                VertexCountFilter filter(VertexCountFilter::EXACT, num);
                double total_area = std::accumulate(shapes.begin(), shapes.end(), 0.0,
                                                    [&filter](double sum, const Polygon &p)
                                                    { return sum + (filter(p) ? getArea(p) : 0.0); });
                std::cout << std::fixed << std::setprecision(1) << total_area << "\n";
            }
            catch (...)
            {
                std::cout << "<INVALID COMMAND>\n";
            }
        }
    }

    void handleMaxMin(std::stringstream &ss, std::vector<Polygon> &shapes, const std::string &cmd)
    {
        std::string sub;
        if (!(ss >> sub) || shapes.empty())
        {
            std::cout << "<INVALID COMMAND>\n";
            return;
        }

        if (sub == "AREA")
        {
            auto it = std::max_element(shapes.begin(), shapes.end(),
                                       [cmd](const Polygon &a, const Polygon &b)
                                       {
                                           return cmd == "MAX" ? (getArea(a) < getArea(b))
                                           : (getArea(a) > getArea(b));
                                       });
            std::cout << std::fixed << std::setprecision(1) << getArea(*it) << "\n";
        }
        else if (sub == "VERTEXES")
        {
            auto it = std::max_element(shapes.begin(), shapes.end(),
                                       [cmd](const Polygon &a, const Polygon &b)
                                       {
                                           return cmd == "MAX" ? (a.points.size() < b.points.size())
                                           : (a.points.size() > b.points.size());
                                       });
            std::cout << it->points.size() << "\n";
        }
        else
        {
            std::cout << "<INVALID COMMAND>\n";
        }
    }

    void handleCount(std::stringstream &ss, std::vector<Polygon> &shapes)
    {
        std::string sub;
        if (!(ss >> sub))
        {
            std::cout << "<INVALID COMMAND>\n";
            return;
        }

        if (filter_map.count(sub))
        {
            VertexCountFilter filter(filter_map.at(sub));
            std::cout << std::count_if(shapes.begin(), shapes.end(), filter) << "\n";
        }
        else
        {
            try
            {
                size_t num = std::stoull(sub);
                if (num < 3)
                {
                    std::cout << "<INVALID COMMAND>\n";
                    return;
                }
                VertexCountFilter filter(VertexCountFilter::EXACT, num);
                std::cout << std::count_if(shapes.begin(), shapes.end(), filter) << "\n";
            }
            catch (...)
            {
                std::cout << "<INVALID COMMAND>\n";
            }
        }
    }

    void handleRmEcho(std::stringstream &ss, std::vector<Polygon> &shapes)
    {
        Polygon target;
        std::string trailing;
        if (!(ss >> target) || (ss >> trailing))
        {
            std::cout << "<INVALID COMMAND>\n";
            return;
        }

        size_t removed = 0;
        auto it = shapes.begin();
        while (it != shapes.end())
        {
            if (*it == target)
            {
                auto start = it;
                while (it != shapes.end() && *it == target)
                {
                    ++it;
                }
                size_t count = std::distance(start, it);
                if (count > 1)
                {
                    removed += count - 1;
                    it = shapes.erase(start + 1, it);
                }
            }
            else
            {
                ++it;
            }
        }
        std::cout << removed << "\n";
    }

    void handleInframe(std::stringstream &ss, std::vector<Polygon> &shapes)
    {
        Polygon target;
        std::string trailing;
        if (!(ss >> target) || (ss >> trailing))
        {
            std::cout << "<INVALID COMMAND>\n";
            return;
        }

        if (shapes.empty())
        {
            std::cout << "<FALSE>\n";
            return;
        }

        auto global_bounds = std::accumulate(
            std::next(shapes.begin()),
                                             shapes.end(),
                                             getBounds(shapes[0]),
                                             [](std::pair<Point, Point> acc, const Polygon &poly)
                                             {
                                                 auto b = getBounds(poly);
                                                 acc.first.x = std::min(acc.first.x, b.first.x);
                                                 acc.first.y = std::min(acc.first.y, b.first.y);
                                                 acc.second.x = std::max(acc.second.x, b.second.x);
                                                 acc.second.y = std::max(acc.second.y, b.second.y);
                                                 return acc;
                                             });

        std::cout << (inBounds(target, global_bounds) ? "<TRUE>" : "<FALSE>") << "\n";
    }

    void processCommands(std::vector<Polygon> &shapes)
    {
        std::string line;
        iofmtguard guard(std::cout);
        std::cout << std::fixed << std::setprecision(1);

        using CommandHandler = std::function<void(std::stringstream &, std::vector<Polygon> &)>;

        const std::map<std::string, CommandHandler> cmd_map = {
            {"AREA", handleArea},
            {"COUNT", handleCount},
            {"RMECHO", handleRmEcho},
            {"INFRAME", handleInframe},
            {"MAX", std::bind(handleMaxMin, std::placeholders::_1, std::placeholders::_2, "MAX")},
            {"MIN", std::bind(handleMaxMin, std::placeholders::_1, std::placeholders::_2, "MIN")}};

            while (std::getline(std::cin, line))
            {
                if (line.empty())
                    continue;
                std::stringstream ss(line);
                std::string cmd;
                if (!(ss >> cmd))
                {
                    std::cout << "<INVALID COMMAND>\n";
                    continue;
                }

                if (cmd_map.count(cmd))
                {
                    cmd_map.at(cmd)(ss, shapes);
                }
                else
                {
                    std::cout << "<INVALID COMMAND>\n";
                }
            }
    }
