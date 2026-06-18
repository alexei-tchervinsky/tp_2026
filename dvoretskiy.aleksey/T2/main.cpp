#include "DataStruct.hpp"

#include <algorithm>
#include <iostream>
#include <iterator>
#include <limits>
#include <vector>

int main()
{
  std::vector<DataStruct> data;

  while (!std::cin.eof())
  {
    std::copy(
        std::istream_iterator<DataStruct>(std::cin),
        std::istream_iterator<DataStruct>(),
        std::back_inserter(data));

    if (std::cin.fail() && !std::cin.eof())
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }

  std::sort(data.begin(), data.end(), DataStructComparator{});

  std::copy(
      data.begin(),
      data.end(),
      std::ostream_iterator<DataStruct>(std::cout, "\n"));

  return 0;
}
