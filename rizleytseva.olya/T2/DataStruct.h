#ifndef DATASTRUCT_H
#define DATASTRUCT_H

#include <iostream>
#include <string>
#include <complex>

struct DataStruct {
    unsigned long long key1;
    char key2;
    std::string key3;

    DataStruct();
    DataStruct(unsigned long long k1, char k2,
               const std::string& k3);
    DataStruct(const DataStruct& other);
    DataStruct(DataStruct&& other) noexcept;

    DataStruct& operator=(const DataStruct& other);
    DataStruct& operator=(DataStruct&& other) noexcept;

    friend std::istream& operator>>(std::istream& is,
                                    DataStruct& data);
    friend std::ostream& operator<<(std::ostream& os,
                                    const DataStruct& data);

    void swap(DataStruct& other) noexcept;

private:
    static bool parseKey1(const std::string& valueStr,
                          unsigned long long& result);
    static bool parseKey2(const std::string& valueStr,
                          char& result);
    static bool parseKey3(const std::string& valueStr,
                          std::string& result);
};

struct DataStructComparator {
    bool operator()(const DataStruct& lhs,
                    const DataStruct& rhs) const;
};

#endif

