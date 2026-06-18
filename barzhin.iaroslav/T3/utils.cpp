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

std::vector<Polygon> Utils::load_from_file(const char* filename) {
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

bool Utils::is_unsigned_number(const std::string &value) {
    return !value.empty() && std::all_of(value.begin(), value.end(), [](unsigned char c) {
        return std::isdigit(c) != 0;
    });
};

double Utils::area_even_odd(const std::vector<Polygon>& data, bool odd) {
    return std::accumulate(data.begin(), data.end(), 0.0,
        [odd](double acc, const Polygon& p) {
            bool is_target = (p.getPoints().size() % 2 != 0);
            if (odd != is_target) return acc;
            return acc + p.getArea();
        }
    );
}

double Utils::area_mean(const std::vector<Polygon>& data) {
    if (data.empty()) throw std::runtime_error("Empty collection");
    return std::accumulate(data.begin(), data.end(), 0.0,
        [](double acc, const Polygon& p) {
            return acc + p.getArea();
        }
    ) / data.size();
}

double Utils::area_num(const std::vector<Polygon>& data, std::size_t num_of_vertexes) {
    return std::accumulate(data.begin(), data.end(), 0.0,
        [num_of_vertexes](double acc, const Polygon& p) {
            if (p.getPoints().size() != num_of_vertexes) return acc;
            return acc + p.getArea();
        }
    );
}

double Utils::max_area(const std::vector<Polygon>& data) {
    if (data.empty()) throw std::runtime_error("Empty collection");
    auto it = std::max_element(data.begin(), data.end(), [](const Polygon& a, const Polygon& b) {
        return a.getArea() < b.getArea();
    });
    return (*it).getArea();
}

double Utils::min_area(const std::vector<Polygon>& data) {
    if (data.empty()) throw std::runtime_error("Empty collection");
    auto it = std::min_element(data.begin(), data.end(), [](const Polygon& a, const Polygon& b) {
        return a.getArea() < b.getArea();
    });
    return (*it).getArea();
}

std::size_t Utils::max_vertexes(const std::vector<Polygon>& data) {
    if (data.empty()) throw std::runtime_error("Empty collection");
    auto it = std::max_element(data.begin(), data.end(),
        [](const Polygon& a, const Polygon& b) {
            return a.getPoints().size() < b.getPoints().size();
        }
    );
    return it->getPoints().size();
}

std::size_t Utils::min_vertexes(const std::vector<Polygon>& data) {
    if (data.empty()) throw std::runtime_error("Empty collection");
    auto it = std::min_element(data.begin(), data.end(),
        [](const Polygon& a, const Polygon& b) {
            return a.getPoints().size() < b.getPoints().size();
        }
    );
    return it->getPoints().size();
}

std::size_t Utils::count_even_odd(const std::vector<Polygon>& data, bool odd) {
    return std::count_if(data.begin(), data.end(),
        [odd](const Polygon& p) {
            bool is_target = (p.getPoints().size() % 2 != 0);
            return odd == is_target;
        }
    );
}

std::size_t Utils::count_num(const std::vector<Polygon>& data, std::size_t num_of_vertexes) {
    return std::count_if(data.begin(), data.end(),
        [num_of_vertexes](const Polygon& p) {
            return p.getPoints().size() == num_of_vertexes;
        }
    );
}

void Utils::cmd_MAX(const std::vector<Polygon>& data, std::istream& is, std::ostream& os) {
    if (data.empty()) throw std::runtime_error("Empty collection");

    std::string sub;
    if (!(is >> sub)) {
        throw std::invalid_argument("");
        return;
    }

    if (sub == "AREA") {
        os << max_area(data) << std::endl;
    } else if (sub == "VERTEXES") {
        os << max_vertexes(data) << std::endl;
    } else {
        throw std::invalid_argument("");
    }
}

void Utils::cmd_MIN(const std::vector<Polygon>& data, std::istream& is, std::ostream& os) {
    if (data.empty()) throw std::runtime_error("Empty collection");

    std::string sub;
    if (!(is >> sub)) {
        throw std::invalid_argument("");
        return;
    }

    if (sub == "AREA") {
        os << min_area(data) << std::endl;
    } else if (sub == "VERTEXES") {
        os << min_vertexes(data) << std::endl;
    } else {
        throw std::invalid_argument("");
    }
}

void Utils::cmd_AREA(const std::vector<Polygon>& data, std::istream& is, std::ostream& os) {
    if (data.empty()) throw std::runtime_error("Empty collection");

    std::string sub;
    if (!(is >> sub)) {
        throw std::invalid_argument("");
        return;
    }

    if (sub == "EVEN" || sub == "ODD") {
        os << area_even_odd(data, sub == "ODD") << std::endl;
    } else if (sub == "MEAN") {
        os << area_mean(data) << std::endl;
    } else if (Utils::is_unsigned_number(sub)) {
        std::size_t num = std::stoul(sub);
        if (num < 3) {
            throw std::invalid_argument("");
        }
        os << area_num(data, num) << std::endl;
    } else {
        throw std::invalid_argument("");
    }
}

void Utils::cmd_COUNT(const std::vector<Polygon>& data, std::istream& is, std::ostream& os) {
    if (data.empty()) throw std::runtime_error("Empty collection");

    std::string sub;
    if (!(is >> sub)) {
        throw std::invalid_argument("");
        return;
    }

    if (sub == "EVEN" || sub == "ODD") {
        os << count_even_odd(data, sub == "ODD") << std::endl;
    } else if (Utils::is_unsigned_number(sub)) {
        std::size_t num = std::stoul(sub);
        if (num < 3) {
            throw std::invalid_argument("");
        }
        os << count_num(data, num) << std::endl;
    } else {
        throw std::invalid_argument("");
    }
}

void Utils::cmd_ECHO(std::vector<Polygon> &data, std::istream& is, std::ostream& os) {
    Polygon p;
    if (!(is >> p)) {
        throw std::invalid_argument("");
        return;
    }

    // check if there are extra characters after polygon (not " \t\n\r")
    //   if there are, throw exception
    std::string rest;
    std::getline(is, rest);
    if (rest.find_first_not_of(" \t\n\r") != std::string::npos) {
        throw std::invalid_argument("");
        return;
    }

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

    os << count << std::endl;
}

void Utils::cmd_INFRAME(std::vector<Polygon> &data, std::istream &is, std::ostream &os) {
    Polygon p;
    if (!(is >> p)) {
        throw std::invalid_argument("");
        return;
    }

    std::string rest;
    std::getline(is, rest);
    if (rest.find_first_not_of(" \t\n\r") != std::string::npos) {
        throw std::invalid_argument("");
        return;
    }

    if (data.empty()) {
        os << "<FALSE>" << std::endl;
        return;
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

    os << (p.inBounds(global_bounds) ? "<TRUE>" : "<FALSE>") << std::endl;
}
