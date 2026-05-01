#ifndef T3_UTILS_HPP
#define T3_UTILS_HPP

#include <vector>

#include "polygon.hpp"

constexpr std::size_t K_PRECISION = 1;

namespace Utils {
    void setup_iomanip(std::ostream &os);

    std::vector<Polygon> load_from_file(char* filename);

    double cmd_AREA_EVEN_ODD(const std::vector<Polygon> &data, bool odd = false);
    double cmd_AREA_MEAN(const std::vector<Polygon> &data);
    double cmd_AREA_NUM(const std::vector<Polygon> &data, std::size_t num_of_vertexes);
    double cmd_MAX_AREA(const std::vector<Polygon> &data);
    double cmd_MIN_AREA(const std::vector<Polygon> &data);

    std::size_t cmd_MAX_VERTEXES(const std::vector<Polygon> &data);
    std::size_t cmd_MIN_VERTEXES(const std::vector<Polygon> &data);
    std::size_t cmd_COUNT_EVEN_ODD(const std::vector<Polygon> &data, bool odd = false);
    std::size_t cmd_COUNT_NUM(const std::vector<Polygon> &data, std::size_t num_of_vertexes);

    std::size_t cmd_ECHO_POLYGON(std::vector<Polygon> &data, const Polygon &p);
    bool cmd_INFRAME_POLYGON(const std::vector<Polygon> &data, const Polygon &p);
}

#endif // T3_UTILS_HPP
