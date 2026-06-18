#ifndef DATA_STRUCT_HPP
#define DATA_STRUCT_HPP

#include <iostream>
#include <string>
#include <complex>

namespace nspace
{
  struct DataStruct
  {
    std::complex<double> key1;
    double key2;
    std::string key3;

    bool operator<(const DataStruct &other) const;
  };

  struct DelimetrIO
  {
    char exp;
  };

  struct DoubleSciIO
  {
    double &ref;
  };

  struct ComplexLspIO
  {
    std::complex<double> &ref;
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

  std::istream &operator>>(std::istream &in, DataStruct &dest);
  std::ostream &operator<<(std::ostream &out, const DataStruct &src);
}

#endif
