#ifndef DATA_STRUCT_HPP
#define DATA_STRUCT_HPP

#include <string>
#include <iostream>

namespace nspace
{
  struct DataStruct
  {
    char key1;          // CHR LIT [cite: 110]
    double key2;        // DBL SCI [cite: 118]
    std::string key3;   // По условию [cite: 22]
    bool operator<(const DataStruct& other) const;
  };

  struct DelimiterIO { char exp; };
  struct CharIO { char& ref; };      // Для 'c' [cite: 68]
  struct DoubleSciIO { double& ref; }; // Для 1.0e-2 [cite: 41]
  struct StringIO { std::string& ref; };
  struct LabelIO { std::string exp; };

  std::istream& operator>>(std::istream& in, DelimiterIO&& dest);
  std::istream& operator>>(std::istream& in, CharIO&& dest);
  std::istream& operator>>(std::istream& in, DoubleSciIO&& dest);
  std::istream& operator>>(std::istream& in, StringIO&& dest);
  std::istream& operator>>(std::istream& in, LabelIO&& dest);
  std::istream& operator>>(std::istream& in, DataStruct& dest);
  std::ostream& operator<<(std::ostream& out, const DataStruct& dest);
}
#endif
