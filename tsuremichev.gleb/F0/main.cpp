#include <iostream>
#include <string>
#include <iomanip>
#include <cmath>
#include <map>
#include "huffman.hpp"

double calculateEntropy(const std::string &text)
{
  if (text.empty())
    return 0.0;

  std::map<unsigned char, size_t> freqs;
  for (char c : text)
    freqs[static_cast<unsigned char>(c)]++;

  double entropy = 0.0;
  double len = static_cast<double>(text.length());

  for (std::map<unsigned char, size_t>::const_iterator it = freqs.begin(); it != freqs.end(); ++it)
  {
    double p = static_cast<double>(it->second) / len;
    entropy -= p * std::log2(p);
  }
  return entropy;
}

int main()
{
  setlocale(LC_ALL, "Russian");
  std::cout << "=== Курсовая работа: Алгоритм Хаффмана"
            << "на стандартных библиотеках STL ===\n";
  std::cout << "Введите строку для сжатия: ";

  std::string userInput;
  std::getline(std::cin, userInput);

  if (userInput.empty())
  {
    std::cerr << "Входная строка пуста. Выход.\n";
    return 1;
  }

  try
  {
    HuffmanEncoder encoder;
    encoder.buildTree(userInput);

    std::string encoded = encoder.encode(userInput);
    std::string decoded = encoder.decode(encoded);

    std::cout << "\n Построенная таблица префиксных кодов:\n";
    encoder.printTable();

    std::cout << "\n Результаты тестирования:\n";
    std::cout << "  Входная строка:   " << userInput << "\n";
    std::cout << "  Битовый поток:    " << encoded << "\n";
    std::cout << "  Восстановлено:    " << decoded << "\n";

    // Метрики алгоритмической эффективности
    double origBits = userInput.length() * 8.0;
    double compBits = encoded.length();
    double compressionRatio = origBits / compBits;
    double textEntropy = calculateEntropy(userInput);
    double avgCodeLen = compBits / static_cast<double>(userInput.length());

    std::cout << "\n=================================="
              << "================================\n";
    std::cout << "                     АНАЛИЗ ЭФФЕКТИВНОСТИ"
              << "                         \n";
    std::cout << "==========================================="
              << "=======================\n";
    std::cout << "  Размер исходного текста        : " << origBits << " бит\n";
    std::cout << "  Размер сжатого битового потока : " << compBits << " бит\n";
    std::cout << "  Информационная энтропия данных : " << std::fixed
              << std::setprecision(4) << textEntropy << " бит/символ\n";
    std::cout << "  Средняя длина кода Хаффмана    : " << avgCodeLen << " бит/символ\n";
    std::cout << "  Коэффициент сжатия (Kсж)       : " << compressionRatio << "\n";
    std::cout << "==================================================================\n";
  }
  catch (const std::exception &ex)
  {
    std::cerr << "\n[ПЕРЕХВАЧЕНО ИСКЛЮЧЕНИЕ]: " << ex.what() << "\n";
    return 1;
  }
  return 0;
}
