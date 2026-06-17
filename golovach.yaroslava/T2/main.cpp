#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <limits>
#include "DataStruct.hpp"

int main()
{
    std::vector<DataStruct> data;

    std::istream_iterator<DataStruct> input_iterator(std::cin);
    std::istream_iterator<DataStruct> end_of_stream;

    while (input_iterator != end_of_stream)
    {
        data.push_back(*input_iterator);
        ++input_iterator;
        
        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            input_iterator = std::istream_iterator<DataStruct>(std::cin);
        }
    }

    std::sort(data.begin(), data.end(), compareDataStruct);

    std::ostream_iterator<DataStruct> output_iterator(std::cout, "\n");
    std::copy(data.begin(), data.end(), output_iterator);

    return 0;
}

