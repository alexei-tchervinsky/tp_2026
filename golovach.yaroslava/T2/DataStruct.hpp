#ifndef DATA_STRUCT_HPP
#define DATA_STRUCT_HPP

#include <string>
#include <iostream>

struct DataStruct
{
    double key1;       // DBL SCI
    char key2;         // CHR LIT
    std::string key3;  // String
};

bool compareDataStruct(const DataStruct& lhs, const DataStruct& rhs);

std::istream& operator>>(std::istream& in, DataStruct& dest);
std::ostream& operator<<(std::ostream& out, const DataStruct& src);

#endif // DATA_STRUCT_HPP
