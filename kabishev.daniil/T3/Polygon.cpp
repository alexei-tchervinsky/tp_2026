#include "Polygon.hpp"
#include <iterator>
#include <algorithm>

// координаты
std::istream& operator>>(std::istream& in, Point& point) {
    char ch1 = 0, ch2 = 0, ch3 = 0;
    int x = 0, y = 0;

    // флаг skipws
    in >> ch1 >> x >> ch2 >> y >> ch3;

    if (in && (ch1 == '(' && ch2 == ';' && ch3 == ')')) {
        point.x = x;
        point.y = y;
    } else {
        in.setstate(std::ios::failbit);
    }
    return in;
}

// обзор
std::istream& operator>>(std::istream& in, Polygon& polygon) {
    size_t num_vertices = 0;
    if (!(in >> num_vertices)) {
        return in;
    }

    if (num_vertices < 3) {
        in.setstate(std::ios::failbit);
        polygon.points.clear(); // очистка мусора
        return in;
    }

    std::vector<Point> temp_points;
    temp_points.reserve(num_vertices);

    // без цикла
    std::copy_n(std::istream_iterator<Point>(in), num_vertices, std::back_inserter(temp_points));

    if (in) {
        polygon.points = std::move(temp_points);
    } else {
        polygon.points.clear();
    }
    return in;
}
