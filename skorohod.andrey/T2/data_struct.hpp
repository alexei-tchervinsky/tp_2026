#ifndef DATA_STRUCT_HPP
#define DATA_STRUCT_HPP

#include <string>

namespace asik
{
  struct DataStruct
  {
    char key1;
    std::pair<long long, unsigned long long> key2;
    std::string key3;
    bool operator < (const DataStruct & other) const;
  };

  struct DelimiterIO
  {
    char exp;
  };

  struct RatLspIO
  {
    std::pair<long long, unsigned long long>& ref;
  };

  struct StringIO
  {
    std::string& ref;
  };

  struct CharIO
  {
    char& ref;
  };

  std::istream& operator>>(std::istream& in, DelimiterIO&& dest);
  std::istream& operator>>(std::istream& in, RatLspIO&& dest);
  std::istream& operator>>(std::istream& in, StringIO&& dest);
  std::istream& operator>>(std::istream& in, CharIO&& dest);
  std::istream& operator>>(std::istream& in, DataStruct& dest);
  std::ostream& operator<<(std::ostream& out, const DataStruct& dest);
}

#endif
