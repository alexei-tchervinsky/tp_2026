#ifndef DATA_STRUCT_HPP
#define DATA_STRUCT_HPP

#include <iostream>
#include <string>

struct DataStruct
{
  double key1;
  unsigned long long key2;
  std::string key3;
};

struct DelimiterIO
{
  char expected;
};

struct DblLitIO
{
  double &ref;
};

struct UllHexIO
{
  unsigned long long &ref;
};

struct StringIO
{
  std::string &ref;
};

bool compareDataStruct(const DataStruct &a, const DataStruct &b);

std::istream &operator>>(std::istream &in, DelimiterIO &&dest);
std::istream &operator>>(std::istream &in, DblLitIO &&dest);
std::istream &operator>>(std::istream &in, UllHexIO &&dest);
std::istream &operator>>(std::istream &in, StringIO &&dest);
std::istream &operator>>(std::istream &in, DataStruct &dest);
std::ostream &operator<<(std::ostream &out, const DataStruct &src);

#endif
