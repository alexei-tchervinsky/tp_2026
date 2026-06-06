#include "ds.hpp"
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

int main() {
    std::vector<DataStruct> vec;

    std::copy(std::istream_iterator<DataStruct>(std::cin),
              std::istream_iterator<DataStruct>(),
              std::back_inserter(vec));

    std::sort(vec.begin(), vec.end(), comparator);

    std::copy(vec.begin(), vec.end(),
              std::ostream_iterator<DataStruct>(std::cout, "\n"));

    return 0;
}
