#ifndef DATA_STRUCT_HPP
#define DATA_STRUCT_HPP

#include <string>
#include <utility>
#include <iostream>

namespace kabishev {
    struct DataStruct {
        unsigned long long key1;
        std::pair<long long, unsigned long long> key2;
        std::string key3;
    };

    std::istream& operator>>(std::istream& in, DataStruct& dest);
    std::ostream& operator<<(std::ostream& out, const DataStruct& src);

    bool compareDataStruct(const DataStruct& a, const DataStruct& b);
}

#endif
