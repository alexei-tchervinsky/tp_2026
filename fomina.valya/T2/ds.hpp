#ifndef DS_HPP
#define DS_HPP

#include <iostream>
#include <string>

struct DataStruct {
    unsigned long long key1;
    double key2;
    std::string key3;
};

std::istream& operator>>(std::istream& in, DataStruct& data);
std::ostream& operator<<(std::ostream& out, const DataStruct& data);
bool comparator(const DataStruct& a, const DataStruct& b);

#endif
