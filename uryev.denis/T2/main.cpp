#include "T2.hpp"
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <limits>

int main() {
  std::vector<DataStruct> data;
  while (!std::cin.eof()) {
    DataStruct temp;
    if (std::cin >> temp) {
      data.push_back(temp);
    }
    else {
      if (std::cin.eof()) break;

      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }
  std::sort(data.begin(), data.end(), [](const DataStruct& a, const DataStruct& b) {
    if (a.key1 != b.key1) return a.key1 < b.key1;
    if (a.key2 != b.key2) return a.key2 < b.key2;
    return a.key3.length() < b.key3.length();
    });
  std::copy(
    data.begin(),
    data.end(),
    std::ostream_iterator<DataStruct>(std::cout, "\n")
  );

  return 0;
}
