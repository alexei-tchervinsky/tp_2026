#ifndef DATA_STRUCT_HPP
#define DATA_STRUCT_HPP

#include <string>
#include <utility>
#include <iostream>

struct DataStruct {
    unsigned long long key1;
    std::pair<long long, unsigned long long> key2;
    std::string key3;
};

std::istream& operator>>(std::istream& is, DataStruct& data);
std::ostream& operator<<(std::ostream& os, const DataStruct& data);

#endif
