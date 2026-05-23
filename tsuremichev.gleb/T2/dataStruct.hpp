#ifndef DATASTRUCT_HPP
#define DATASTRUCT_HPP

#include <iostream>
#include <string>
#include <complex>
#include <cmath>

struct DataStruct
{
  double key1;               // DBL SCI
  std::complex<double> key2; // CMP LSP
  std::string key3;
};

// Вспомогательная структура для парсинга фиксированных символов (разделителей)
// struct DelimiterIO
// {
//   char expected;
// };

// // Вспомогательная структура для парсинга меток (например, ":key1")
// struct LabelIO
// {
//   std::string expected;
// };

std::istream &operator>>(std::istream &in, DataStruct &dest);
std::ostream &operator<<(std::ostream &out, const DataStruct &src);
bool compareDataStruct(const DataStruct &a, const DataStruct &b);
#endif // DATASTRUCT_HPP
