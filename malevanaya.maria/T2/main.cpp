#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include "data_struct.hpp"

int main() {
    std::vector<DataStruct> data;

    std::copy(
        std::istream_iterator<DataStruct>(std::cin),
        std::istream_iterator<DataStruct>(),
        std::back_inserter(data)
    );

    std::sort(data.begin(), data.end(), compareDataStruct);

    std::copy(
        std::begin(data),
        std::end(data),
        std::ostream_iterator<DataStruct>(std::cout, "\n")
    );

    return 0;
}
