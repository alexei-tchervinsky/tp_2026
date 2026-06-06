#ifndef DATA_STRUCT_H
#define DATA_STRUCT_H

#include <iostream>
#include <string>

struct DataStruct {
    char key1;
    unsigned long long key2;
    std::string key3;
};

std::istream& operator>>(std::istream& in, DataStruct& data);
std::ostream& operator<<(std::ostream& out, const DataStruct& data);
bool comparator(const DataStruct& a, const DataStruct& b);

#endif
