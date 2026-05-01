#include "utils.hpp"

#include <iomanip>
#include <fstream>
#include <iterator>
#include <numeric>
#include <algorithm>
#include <sstream>

void Utils::setup_iomanip(std::ostream &os) {
    os << std::setprecision(K_PRECISION) << std::fixed;
}

std::vector<Polygon> Utils::load_from_file(char* filename) {
    std::ifstream file(filename);
    std::vector<Polygon> result;

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream line_stream(line);
        Polygon polygon;

        if ((line_stream >> polygon) && (line_stream >> std::ws).eof()) {
            result.push_back(std::move(polygon));
        }
    }

    return result;
}

double Utils::cmd_AREA_EVEN_ODD(const std::vector<Polygon>& data, bool odd) {
    return std::accumulate(data.begin(), data.end(), 0.0,
        [odd](double acc, const Polygon& p) {
            bool is_target = (p.getPoints().size() % 2 != 0);
            if (odd != is_target) return acc;
            return acc + p.getArea();
        }
    );
}

double Utils::cmd_AREA_MEAN(const std::vector<Polygon> &data) {
    if (data.empty()) throw std::runtime_error("Empty collection");
    return std::accumulate(data.begin(), data.end(), 0.0,
        [](double acc, const Polygon& p) {
            return acc + p.getArea();
        }
    ) / data.size();
}

double Utils::cmd_AREA_NUM(const std::vector<Polygon> &data, std::size_t num_of_vertexes) {
    return std::accumulate(data.begin(), data.end(), 0.0,
        [num_of_vertexes](double acc, const Polygon& p) {
            if (p.getPoints().size() != num_of_vertexes) return acc;
            return acc + p.getArea();
        }
    );
}

double Utils::cmd_MAX_AREA(const std::vector<Polygon>& data) {
    if (data.empty()) throw std::runtime_error("Empty collection");
    auto it = std::max_element(data.begin(), data.end(), [](const Polygon& a, const Polygon& b) {
        return a.getArea() < b.getArea();
    });
    return (*it).getArea();
}

double Utils::cmd_MIN_AREA(const std::vector<Polygon> &data) {
    if (data.empty()) throw std::runtime_error("Empty collection");
    auto it = std::min_element(data.begin(), data.end(), [](const Polygon& a, const Polygon& b) {
        return a.getArea() < b.getArea();
    });
    return (*it).getArea();
}

std::size_t Utils::cmd_MAX_VERTEXES(const std::vector<Polygon> &data) {
    if (data.empty()) throw std::runtime_error("Empty collection");

    auto it = std::max_element(data.begin(), data.end(),
        [](const Polygon& a, const Polygon& b) {
            return a.getPoints().size() < b.getPoints().size();
        }
    );
    return it->getPoints().size();
}

std::size_t Utils::cmd_MIN_VERTEXES(const std::vector<Polygon> &data) {
    if (data.empty()) throw std::runtime_error("Empty collection");

    auto it = std::min_element(data.begin(), data.end(),
        [](const Polygon& a, const Polygon& b) {
            return a.getPoints().size() < b.getPoints().size();
        }
    );
    return it->getPoints().size();
}

std::size_t Utils::cmd_COUNT_EVEN_ODD(const std::vector<Polygon> &data, bool odd) {
    return std::count_if(data.begin(), data.end(),
        [odd](const Polygon& p) {
            bool is_target = (p.getPoints().size() % 2 != 0);
            return odd == is_target;
        }
    );
}

std::size_t Utils::cmd_COUNT_NUM(const std::vector<Polygon> &data, std::size_t num_of_vertexes) {
    return std::count_if(data.begin(), data.end(),
        [num_of_vertexes](const Polygon& p) {
            return p.getPoints().size() == num_of_vertexes;
        }
    );
}

std::size_t Utils::cmd_ECHO_POLYGON(std::vector<Polygon> &data, const Polygon &p) {
    std::size_t count = std::count(data.begin(), data.end(), p);

    if (count > 0) {
        std::vector<Polygon> result;
        result.reserve(data.size() + count);

        data = std::accumulate(data.begin(), data.end(), std::move(result),
            [&p](std::vector<Polygon> acc, const Polygon &current) {
                acc.push_back(current);
                if (current == p) {
                    acc.push_back(current);
                }
                return acc;
            }
        );
    }

    return count;
}

bool Utils::cmd_INFRAME_POLYGON(const std::vector<Polygon> &data, const Polygon &p) {
    if (data.empty()) {
        return false;
    }

    auto global_bounds = std::accumulate(
        std::next(data.begin()),
        data.end(),
        data[0].getBounds(),
        [](std::pair<Point, Point> acc, const Polygon &poly) {
            auto b = poly.getBounds();
            acc.first.x = std::min(acc.first.x, b.first.x);
            acc.first.y = std::min(acc.first.y, b.first.y);
            acc.second.x = std::max(acc.second.x, b.second.x);
            acc.second.y = std::max(acc.second.y, b.second.y);
            return acc;
        }
    );

    return p.inBounds(global_bounds);
}
