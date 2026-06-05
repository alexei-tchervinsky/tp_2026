#include "data_struct.hpp"

#include <iostream>
#include <string>
#include <iterator>
#include <vector>
#include <limits>
#include <algorithm>

int main()
{
  using asik::DataStruct;
  std::vector<DataStruct> data;
  while (!std::cin.eof())
  {
    if (!std::cin)
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      continue;
    }
    std::copy(std::istream_iterator<DataStruct>(std::cin),\
              std::istream_iterator<DataStruct>(), std::back_inserter(data));
  }
  std::sort(data.begin(), data.end());
  std::copy(std::begin(data), std::end(data),\
            std::ostream_iterator< DataStruct >(std::cout, "\n"));
  return 0;
}
