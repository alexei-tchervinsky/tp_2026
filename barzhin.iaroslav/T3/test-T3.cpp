#include <iostream>
#include <functional>
#include <string>
#include <sstream>
#include <vector>

#include "polygon.hpp"
#include "utils.hpp"

struct TestRunner {
    int total = 0;
    int passed = 0;

    void run(const std::string& name, const std::function<bool()>& test_func) {
        total++;
        if (test_func()) {
            passed++;
            std::cout << "[PASS] " << name << std::endl;
        } else {
            std::cout << "[FAIL] " << name << std::endl;
        }
    }

    void summary() const {
        std::cout << "\n--- Result: " << passed << "/" << total
                  << " tests passed ---" << std::endl;
    }
};

bool test_polygon_io() {
    Polygon p;
    p.addPoint({0, 0});
    p.addPoint({4, 0});
    p.addPoint({0, 3});

    std::stringstream ss;
    ss << p;
    return ss.str() == "3 (0;0) (4;0) (0;3)";
}

bool test_polygon_area() {
    Polygon p;
    p.addPoint({0, 0});
    p.addPoint({4, 0});
    p.addPoint({0, 3});

    return p.getArea() == 6.0;
}

bool test_polygon_bounds() {
    Polygon p;
    p.addPoint({-1, 5});
    p.addPoint({10, 2});
    p.addPoint({3, -4});

    auto bounds = p.getBounds();
    return bounds.first.x == -1 && bounds.first.y == -4 &&
           bounds.second.x == 10 && bounds.second.y == 5;
}

bool test_utils_echo() {
    Polygon p1; p1.addPoint({0,0}); p1.addPoint({1,1}); p1.addPoint({1,0});
    Polygon p2; p2.addPoint({0,0}); p2.addPoint({2,2}); p2.addPoint({2,0});

    std::vector<Polygon> data = {p1, p2, p1};
    std::size_t added = Utils::cmd_ECHO_POLYGON(data, p1);

    return added == 2 && data.size() == 5 && data[1] == p1 && data[4] == p1;
}

bool test_utils_count() {
    Polygon tri; tri.addPoint({0,0}); tri.addPoint({1,1}); tri.addPoint({1,0});
    Polygon rect; rect.addPoint({0,0}); rect.addPoint({0,1}); rect.addPoint({1,1}); rect.addPoint({1,0});

    std::vector<Polygon> data = {tri, rect, tri};

    bool count_odd = Utils::cmd_COUNT_EVEN_ODD(data, true) == 2;
    bool count_even = Utils::cmd_COUNT_EVEN_ODD(data, false) == 1;

    return count_odd && count_even;
}

bool test_invalid_input() {
    std::stringstream ss("3 (0;0) (1,1) (2;2)");
    Polygon p;
    ss >> p;
    return ss.fail();
}

bool test_utils_inframe() {
    Polygon frame;
    frame.addPoint({0,0}); frame.addPoint({10,0}); frame.addPoint({10,10}); frame.addPoint({0,10});

    Polygon inner;
    inner.addPoint({2,2}); inner.addPoint({5,2}); inner.addPoint({5,5});

    Polygon outer;
    outer.addPoint({-1,-1}); outer.addPoint({2,-1}); outer.addPoint({2,2});

    std::vector<Polygon> data = {frame};
    return Utils::cmd_INFRAME_POLYGON(data, inner) == true &&
           Utils::cmd_INFRAME_POLYGON(data, outer) == false;
}

int main() {
    TestRunner tr;

    tr.run("Polygon IO Format", test_polygon_io);
    tr.run("Polygon Area Calculation", test_polygon_area);
    tr.run("Polygon Bounding Box", test_polygon_bounds);
    tr.run("Invalid Polygon Input", test_invalid_input);

    tr.run("Utils ECHO Command", test_utils_echo);
    tr.run("Utils COUNT Command", test_utils_count);
    tr.run("Utils INFRAME Command", test_utils_inframe);

    tr.summary();
    return (tr.total == tr.passed) ? 0 : 1;
}
