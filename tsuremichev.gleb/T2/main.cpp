#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <limits>
#include <cmath>
#include <fstream>
#include "dataStruct.hpp"

int main()
{
  std::vector<DataStruct> data;
  std::ifstream infile("input.txt");

  if (!infile.is_open())
  {
    std::cerr << "Error: could not open input.txt\n";
    return 1;
  }

  std::string line;
  while (std::getline(infile, line))
  {
    if (line.empty())
      continue;

    std::stringstream ss(line);
    DataStruct temp;

    if (ss >> temp)
    {
      data.push_back(temp);
    }
  }

  infile.close();

  std::sort(data.begin(), data.end(), [](const DataStruct &a, const DataStruct &b)
            {
    const double EPS = 1e-9;

    double absA1 = std::abs(a.key1);
    double absB1 = std::abs(b.key1);
    if (std::abs(absA1 - absB1) > EPS) {
      return absA1 < absB1;
    }

    if (std::abs(a.key2 - b.key2) > EPS) {
      return a.key2 < b.key2;
    }

    return a.key3.length() < b.key3.length(); });

  std::copy(
      data.begin(),
      data.end(),
      std::ostream_iterator<DataStruct>(std::cout, "\n"));

  return 0;
}
