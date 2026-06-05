#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <limits>
#include <cmath>
#include <sstream>
#include "dataStruct.hpp"

bool compareDataStruct(
    const DataStruct &a,
    const DataStruct &b)
{
  const double EPS = 1e-9;

  double absA1 = std::abs(a.key1);
  double absB1 = std::abs(b.key1);

  if (std::abs(absA1 - absB1) > EPS)
  {
    return absA1 < absB1;
  }

  if (std::abs(a.key2 - b.key2) > EPS)
  {
    return a.key2 < b.key2;
  }

  return a.key3.length() < b.key3.length();
}

int main()
{
  std::vector<DataStruct> data;
  std::string line;

  while (std::getline(std::cin, line))
  {
    if (line.empty())
    {
      continue;
    }

    std::stringstream ss(line);
    DataStruct temp;

    if (ss >> temp)
    {
      data.push_back(temp);
    }
    else
    {
      std::cin.clear();
    }
  }

  std::sort(
      data.begin(),
      data.end(),
      compareDataStruct);

  std::ostream_iterator<DataStruct> output_iterator(
      std::cout,
      "\n");
  std::copy(
      data.begin(),
      data.end(),
      output_iterator);

  return 0;
}
