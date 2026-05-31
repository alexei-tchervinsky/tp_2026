#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include "data_struct.hpp"

int main() {
    std::vector<kabishev::DataStruct> data;

    std::copy(
        std::istream_iterator<kabishev::DataStruct>(std::cin),
        std::istream_iterator<kabishev::DataStruct>(),
        std::back_inserter(data)
    );

    std::sort(data.begin(), data.end(), kabishev::compareDataStruct);

    std::copy(
        data.begin(),
        data.end(),
        std::ostream_iterator<kabishev::DataStruct>(std::cout, "\n")
    );

    return 0;
}
