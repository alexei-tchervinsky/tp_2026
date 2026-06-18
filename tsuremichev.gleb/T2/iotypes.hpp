#ifndef IOTYPES_HPP
#define IOTYPES_HPP

#include <iostream>
#include <string>
#include <complex>

struct DelimetrIO
{
  char exp;
};

// Структура для комплексного числа [CMP LSP]
struct ComplexLspIO
{
  std::complex<double> &ref;
};

// Структура для double в научном формате [DBL SCI]
struct DoubleSciIO
{
  double &ref;
};

struct StringIO
{
  std::string &ref;
};

struct KeyIO
{
  std::string &ref;
};

std::istream &operator>>(std::istream &in, DelimetrIO &&dest);
std::istream &operator>>(std::istream &in, ComplexLspIO &&dest);
std::istream &operator>>(std::istream &in, DoubleSciIO &&dest);
std::istream &operator>>(std::istream &in, StringIO &&dest);
std::istream &operator>>(std::istream &in, KeyIO &&dest);

#endif
