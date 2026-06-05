#include "DataStruct.hpp"
#include <iostream>
#include <string>
#include <iterator>
#include <vector>
#include <limits>
#include <algorithm>

int main(){
    using nspace::DataStruct;
    std::vector<DataStruct> data;
    while (!std::cin.eof())
  {
    // Пытаемся считать данные до первой ошибки или конца файла
    std::copy(
      std::istream_iterator< DataStruct >(std::cin),
      std::istream_iterator< DataStruct >(),
      std::back_inserter(data)
    );

    // Если copy остановился из-за ошибки (не EOF), чистим поток
    if (std::cin.fail() && !std::cin.eof())
    {
      std::cin.clear();
      // Пропускаем все символы до конца строки, чтобы начать заново
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }

  // Сортировка по вектору с использованием operator<
  std::sort(data.begin(), data.end());

  std::cout << "DataStruct:\n";
  // Вывод с использованием operator<<
  std::copy(
    data.begin(),
    data.end(),
    std::ostream_iterator< DataStruct >(std::cout, "\n")
  );

  return 0;
}
