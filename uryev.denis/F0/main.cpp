#include <iostream>
#include <string>
#include <unordered_map>
#include "TextProcessor.hpp"
#include "Analytics.hpp"

int main()
{
  std::setlocale(LC_ALL, "UTF-8");
  std::unordered_map<std::string, int> word_table;
  TextProcessor processor;
  Analytics analytics;
  std::string filename = "input.txt";
  std::cout << "[Инфо] Начинается обработка файла: " << filename << "..." << std::endl;
  if (!processor.processFile(filename, word_table))
  {
    std::cerr << "[Ошибка] Не удалось открыть или прочитать файл: " << filename << std::endl;
    return 1;
  }
  std::cout << "[Успех] Файл успешно обработан." << std::endl;
  std::cout << "[Инфо] Всего уникальных слов найдено: " << word_table.size() << std::endl;
  analytics.printTop3(word_table);
  return 0;
}
