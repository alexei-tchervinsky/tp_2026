#include "DataStruct.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <limits>

int main()
{
  std::vector< DataStruct > dataVector;

  while (!std::cin.eof())
  {
    if (!std::cin)
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
      continue;
    }

    std::copy(
      std::istream_iterator< DataStruct >(std::cin),
      std::istream_iterator< DataStruct >(),
      std::back_inserter(dataVector)
    );
  }

  std::sort(dataVector.begin(), dataVector.end(), DataStructComparator{});

  std::copy(
    dataVector.begin(),
    dataVector.end(),
    std::ostream_iterator< DataStruct >(std::cout, "\n")
  );

  return 0;
}

