#ifndef DATASTRUCT_HPP
#define DATASTRUCT_HPP

#include <iostream>
#include <string>

namespace tchervinsky
{
    struct DataStruct
    {
        char key1;
        double key2;
        std::string key3;

        bool operator<(const DataStruct& other) const;
    };

    std::istream& operator>>(std::istream& in, DataStruct& ds);
    std::ostream& operator<<(std::ostream& out, const DataStruct& ds);
}

#endif
