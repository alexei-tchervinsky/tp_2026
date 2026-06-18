#include "DataStruct.hpp"
#include <vector>
#include <algorithm>
#include <iterator>

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
      std::string ignore;
      std::getline(std::cin, ignore);
    }
  }
  std::sort(data.begin(), data.end(), compareDataStruct);
  std::copy(
      data.begin(),
      data.end(),
      std::ostream_iterator<DataStruct>(std::cout, "\n"));
  return 0;
}
