#include "data_struct.hpp"

#include <algorithm>
#include <iostream>
#include <iterator>
#include <limits>
#include <vector>

int main() {
    std::vector<nspace::DataStruct> data;

    while (!std::cin.eof()) {
        if (!std::cin) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        std::copy(
            std::istream_iterator<nspace::DataStruct>(std::cin),
            std::istream_iterator<nspace::DataStruct>(),
            std::back_inserter(data)
        );
    }

    std::sort(data.begin(), data.end());

    std::copy(
        data.begin(),
        data.end(),
        std::ostream_iterator<nspace::DataStruct>(std::cout, "\n")
    );

    return 0;
}
