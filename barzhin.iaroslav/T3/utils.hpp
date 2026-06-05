#ifndef T3_UTILS_HPP
#define T3_UTILS_HPP

#include <vector>

#include "polygon.hpp"

constexpr std::size_t K_PRECISION = 1;

namespace Utils {
    void setup_iomanip(std::ostream &os);
    std::vector<Polygon> load_from_file(const char* filename);
    bool is_unsigned_number(const std::string &value);

    double area_even_odd(const std::vector<Polygon>& data, bool odd);
    double area_mean(const std::vector<Polygon>& data);
    double area_num(const std::vector<Polygon>& data, std::size_t num_of_vertexes);
    double max_area(const std::vector<Polygon>& data);
    double min_area(const std::vector<Polygon>& data);
    std::size_t max_vertexes(const std::vector<Polygon>& data);
    std::size_t min_vertexes(const std::vector<Polygon>& data);
    std::size_t count_even_odd(const std::vector<Polygon>& data, bool odd);
    std::size_t count_num(const std::vector<Polygon>& data, std::size_t num_of_vertexes);

    // rewrite done
    void cmd_MAX(const std::vector<Polygon>& data, std::istream& is, std::ostream& os);
    void cmd_MIN(const std::vector<Polygon>& data, std::istream& is, std::ostream& os);
    void cmd_AREA(const std::vector<Polygon>& data, std::istream& is, std::ostream& os);
    void cmd_COUNT(const std::vector<Polygon>& data, std::istream& is, std::ostream& os);
    void cmd_ECHO(std::vector<Polygon> &data, std::istream& is, std::ostream& os);
    void cmd_INFRAME(std::vector<Polygon> &data, std::istream& is, std::ostream& os);
}

#endif // T3_UTILS_HPP
