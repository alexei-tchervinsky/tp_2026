#include "polygon.hpp"
#include "commands.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iterator>
#include <algorithm>

int main(int argc, char* argv[])
{
  if (argc != 2)
  {
    std::cerr << "Ошибка: не указан файл с фигурами" << std::endl;
    return 1;
  }

  std::ifstream file(argv[1]);
  if (!file)
  {
    std::cerr << "Ошибка: не удалось открыть файл " << argv[1] << std::endl;
    return 1;
  }

  std::vector<tchervinsky::Polygon> polygons;

  std::copy(
    std::istream_iterator<tchervinsky::Polygon>(file),
    std::istream_iterator<tchervinsky::Polygon>(),
    std::back_inserter(polygons)
  );

  std::string line;
  while (std::getline(std::cin, line))
  {
    if (line.empty()) continue;
    tchervinsky::processCommand(polygons, line);
  }

  return 0;
}
