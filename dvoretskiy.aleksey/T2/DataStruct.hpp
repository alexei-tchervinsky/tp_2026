#ifndef DATA_STRUCT_HPP
#define DATA_STRUCT_HPP

#include <iosfwd>
#include <string>

struct DataStruct
{
  char key1;
  unsigned long long key2;
  std::string key3;
};

std::istream& operator>>(std::istream& input, DataStruct& data);
std::ostream& operator<<(std::ostream& output, const DataStruct& data);

struct DataStructComparator
{
  bool operator()(const DataStruct& lhs, const DataStruct& rhs) const;
};

#endif
