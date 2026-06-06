#ifndef DATASTRUCT_HPP
#define DATASTRUCT_HPP

#include <iostream>
#include <string>

struct DataStruct
{
  double key1;
  char key2;
  std::string key3;

  bool operator<(const DataStruct& other) const;
};

struct DelimiterIO
{
  char exp;
};

struct DblSciIO
{
  double& ref;
};

struct CharLitIO
{
  char& ref;
};

struct StringIO
{
  std::string& ref;
};

std::istream& operator>>(std::istream& in, DelimiterIO&& dest);
std::istream& operator>>(std::istream& in, DblSciIO&& dest);
std::istream& operator>>(std::istream& in, CharLitIO&& dest);
std::istream& operator>>(std::istream& in, StringIO&& dest);
std::istream& operator>>(std::istream& in, DataStruct& dest);

std::ostream& operator<<(std::ostream& out, const DataStruct& src);

struct DataStructComparator
{
  bool operator()(const DataStruct& lhs, const DataStruct& rhs) const;
};

#endif
