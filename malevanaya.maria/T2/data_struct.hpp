#ifndef DATA_STRUCT_HPP
#define DATA_STRUCT_HPP

#include <string>
#include <complex>
#include <iostream>

struct DataStruct {
    char key1;
    std::complex<double> key2;
    std::string key3;
};

struct DelimiterIO {
    char exp;
};

struct DelimiterNoSkipIO {
    char exp;
};

struct LabelIO {
    std::string exp;
};

struct CharLitIO {
    char& ref;
};

struct CmpLspIO {
    std::complex<double>& ref;
};

struct StringIO {
    std::string& ref;
};

std::istream& operator>>(std::istream& in, DelimiterIO&& dest);
std::istream& operator>>(std::istream& in, DelimiterNoSkipIO&& dest);
std::istream& operator>>(std::istream& in, LabelIO&& dest);
std::istream& operator>>(std::istream& in, CharLitIO&& dest);
std::istream& operator>>(std::istream& in, CmpLspIO&& dest);
std::istream& operator>>(std::istream& in, StringIO&& dest);
std::istream& operator>>(std::istream& in, DataStruct& dest);
std::ostream& operator<<(std::ostream& out, const DataStruct& src);
bool compareDataStruct(const DataStruct& a, const DataStruct& b);

#endif
