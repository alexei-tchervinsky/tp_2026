#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <limits>

#include "dataStruct.hpp"

int main()
{
  std::vector<nspace::DataStruct> data;

  while (!std::cin.eof())
  {
    std::copy(
        std::istream_iterator<nspace::DataStruct>(std::cin),
        std::istream_iterator<nspace::DataStruct>(),
        std::back_inserter(data));

    if (std::cin.fail() && !std::cin.eof())
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }

  std::sort(data.begin(), data.end());

  std::copy(data.begin(), data.end(),
            std::ostream_iterator<nspace::DataStruct>(std::cout, "\n"));

  return 0;
}
