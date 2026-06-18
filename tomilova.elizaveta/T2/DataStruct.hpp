#ifndef DATASTRUCT_HPP
#define DATASTRUCT_HPP

#include <iostream>
#include <vector>
#include <string>
#include <complex>

namespace nspace{
struct DataStruct
{
    char key1;
    std::complex<double> key2;
    std::string key3;

    bool operator < (const DataStruct & other) const;
};
// Вспомогательные структуры для парсинга
struct DelimiterIO {
    char exp;
};
struct CharIO {
    char & ref;
};
struct ComplexIO {
    std::complex<double> & ref;
};
struct StringIO {
    std::string & ref;
};

std::istream& operator>>(std::istream& in, DelimiterIO&& dest);
std::istream& operator>>(std::istream& in, CharIO&& dest);
std::istream& operator>>(std::istream& in, ComplexIO&& dest);
std::istream& operator>>(std::istream& in, StringIO&& dest);
std::istream& operator>>(std::istream& in, DataStruct& dest);
std::ostream& operator<<(std::ostream& out, const DataStruct& src);
}
#endif //DATASTRUCT_HPP
