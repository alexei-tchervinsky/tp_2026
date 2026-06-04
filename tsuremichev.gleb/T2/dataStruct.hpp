#ifndef DATASTRUCT_HPP
#define DATASTRUCT_HPP

#include <iostream>
#include <string>
#include <complex>

struct DataStruct
{
  std::complex<double> key1; // CMP LSP
  double key2;               // DBL SCI
  std::string key3;

  DataStruct() : key1(0.0, 0.0), key2(0.0), key3("") {}
};

struct DelimiterIO
{
  char expected;
};
struct LabelIO
{
  std::string expected;
};

std::istream &operator>>(std::istream &in, DelimiterIO &&dest);
std::istream &operator>>(std::istream &in, LabelIO &&dest);
std::istream &operator>>(std::istream &in, DataStruct &dest);
std::ostream &operator<<(std::ostream &out, const DataStruct &src);

#endif
