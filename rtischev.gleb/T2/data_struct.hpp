#ifndef DATA_STRUCT_H
#define DATA_STRUCT_H

#include <iostream>
#include <string>
#include <utility>
#include <limits>
#include "iotypes.hpp"
#include "iofmtguard.hpp"

struct DataStruct
{
    unsigned long long key1 = 0;
    std::pair<long long, unsigned long long> key2;
    std::string key3;
};

std::istream &operator>>(std::istream &in, DataStruct &dest);
std::ostream &operator<<(std::ostream &out, const DataStruct &src);
bool operator<(const DataStruct &lhs, const DataStruct &rhs);

#endif
