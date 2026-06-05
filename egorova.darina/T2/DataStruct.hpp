#ifndef DATA_STRUCT_HPP
#define DATA_STRUCT_HPP

#include <complex>
#include <string>
#include <iostream>

struct DataStruct {
    std::complex<double> key1;
    char key2;
    std::string key3;
};

struct DelimiterIO {
    char exp;
};

struct LabelIO {
    std::string exp;
};

std::istream& operator>>(std::istream& in, DelimiterIO&& dest);
std::istream& operator>>(std::istream& in, LabelIO&& dest);
std::istream& operator>>(std::istream& in, DataStruct& dest);
std::ostream& operator<<(std::ostream& out, const DataStruct& src);

bool compareDataStruct(const DataStruct& a, const DataStruct& b);

#endif
