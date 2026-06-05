#ifndef DATA_STRUCT_HPP
#define DATA_STRUCT_HPP

#include <string>
#include <iostream>

namespace nspace{
  struct DataStruct{
    char key1;
    unsigned long long key2;
    std::string key3;

    bool operator<(const DataStruct& other) const;
  };

  struct DelimiterIO{
    char exp;
  };

  struct CharLitIO{
    char& ref;
  };

  struct UllHexIO{
    unsigned long long& ref;
  };

  struct StringIO{
    std::string& ref;
  };

  std::istream& operator>>(std::istream& in, DelimiterIO&& dest);
  std::istream& operator>>(std::istream& in, CharLitIO&& dest);
  std::istream& operator>>(std::istream& in, UllHexIO&& dest);
  std::istream& operator>>(std::istream& in, StringIO&& dest);
  std::istream& operator>>(std::istream& in, DataStruct& dest);
  std::ostream& operator<<(std::ostream& out, const DataStruct& dest);
}

#endif
