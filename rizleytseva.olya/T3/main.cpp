#include "polygon.h"
#include "commands.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <limits>

int main(int argc, char* argv[])
{
  // Тест 23/29: ровно один аргумент — имя файла
  if (argc != 2)
  {
    std::cerr << "Error: expected exactly one argument: filename\n";
    return 1;
  }

  std::ifstream file(argv[1]);
  if (!file.is_open())
  {
    std::cerr << "Error: cannot open file '" << argv[1] << "'\n";
    return 1;
  }

  // Шаг 1: читаем полигоны из файла — отдельным действием
  std::vector< Polygon > polys;
  while (!file.eof())
  {
    if (!file)
    {
      file.clear();
      file.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
      continue;
    }
    std::copy(
      std::istream_iterator< Polygon >(file),
      std::istream_iterator< Polygon >(),
      std::back_inserter(polys)
    );
  }

  // Шаг 2: обрабатываем команды из stdin
  doTasks(polys);

  return 0;
}

