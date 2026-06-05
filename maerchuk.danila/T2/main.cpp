#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <limits>
#include "data_struct.hpp"

int main()
{
  using nspace::DataStruct;
  std::vector<DataStruct> data;

  while (!std::cin.eof())
  {
    // std::copy для чтения блока данных до первой ошибки
    std::copy(
      std::istream_iterator<DataStruct>(std::cin),
      std::istream_iterator<DataStruct>(),
      std::back_inserter(data)
    );

    if (std::cin.fail() && !std::cin.eof())
    {
      std::cin.clear(); // Сбрасываем флаг ошибки
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }

  // Сортировка [cite: 6, 7, 8, 9, 10]
  std::sort(data.begin(), data.end());

  // Вывод с использованием std::copy и итератора потока [cite: 12]
  std::copy(
    data.begin(),
    data.end(),
    std::ostream_iterator<DataStruct>(std::cout, "\n")
  );

  return 0;
}
