#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iterator>
#include "polygon.hpp"

// для проверки пробела между точками
bool read_space(std::istream &in)
{
    char ch = 0;
    in >> std::noskipws >> ch;
    return ch == ' ';
}

// оператор сравнения
bool operator==(const Polygon &lhs, const Polygon &rhs)
{
    if (lhs.points.size() != rhs.points.size())
    {
        return false;
    }
    return std::equal(lhs.points.begin(), lhs.points.end(), rhs.points.begin(),
                      [](const Point &p1, const Point &p2)
                      {
                          return p1.x == p2.x && p1.y == p2.y;
                      });
}

std::istream &operator>>(std::istream &in, Point &point)
{
    std::istream::sentry sentry(in);
    if (!sentry)
    {
        return in;
    }

    char ch1 = 0, ch2 = 0, ch3 = 0;
    int x = 0, y = 0;
    in >> ch1 >> x >> ch2 >> y >> ch3;

    if (in)
    {
        if (ch1 == '(' && ch2 == ';' && ch3 == ')')
        {
            point = Point{x, y};
        }
        else
        {
            in.setstate(std::ios_base::failbit);
        }
    }
    return in;
}

std::istream &operator>>(std::istream &in, Polygon &polygon)
{
    std::istream::sentry sentry(in);
    if (!sentry)
    {
        return in;
    }

    std::string line;
    if (!std::getline(in, line))
    {
        return in;
    }

    std::stringstream input(line);
    size_t vertex_count = 0;

    if (!(input >> vertex_count) || vertex_count < 3)
    {
        in.setstate(std::ios_base::failbit);
        return in;
    }

    std::vector<Point> temp_points;

    for (size_t i = 0; i < vertex_count; ++i)
    {
        // проверка на пробел
        if (!read_space(input))
        {
            in.setstate(std::ios_base::failbit);
            return in;
        }

        Point p;
        if (!(input >> p))
        {
            in.setstate(std::ios_base::failbit);
            return in;
        }
        temp_points.push_back(p);
    }

    char extra = 0;
    if (input >> std::noskipws >> extra)
    {
        in.setstate(std::ios_base::failbit);
        return in;
    }

    polygon.points = std::move(temp_points);

    return in;
}
