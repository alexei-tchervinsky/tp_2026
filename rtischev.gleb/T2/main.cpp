#include "data_struct.hpp"
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

int main() {
    std::vector<DataStruct> vec;

    std::copy(
        std::istream_iterator<DataStruct>(std::cin),
              std::istream_iterator<DataStruct>(),
              std::back_inserter(vec)
    );

    std::sort(vec.begin(), vec.end(), [](const DataStruct& a, const DataStruct& b) -> bool {
        if (a.key1 != b.key1) {
            return a.key1 < b.key1;
        }
        double value_a = (double)a.key2.first / a.key2.second;
        double value_b = (double)b.key2.first / b.key2.second;
        if (value_a > value_b) {
            return false;
        } else if (value_a < value_b) {
            return true;
        }
        return a.key3.length() < b.key3.length();
    });

    for (const auto& item : vec) {
        std::cout << item << std::endl;
    }

    return 0;
}
