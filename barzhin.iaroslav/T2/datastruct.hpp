#ifndef DATASTRUCT_HPP
#define DATASTRUCT_HPP

#include <complex>
#include <utility>
#include <string>

namespace ds {
    struct DataStruct {
        std::complex<double> key1;
        std::pair<long long, unsigned long long> key2;
        std::string key3;

        bool operator<(DataStruct const& other) const;
    };

    struct DelimiterIO {
        char exp;
    };

    struct DoubleIO {
        double& ref;
    };

    struct ComplexIO {
        std::complex<double>& ref;
    };

    struct RationalIO {
        std::pair<long long, unsigned long long>& ref;
    };

    struct StringIO {
        std::string& ref;
    };

    struct LabelIO {
        std::string exp;
    };

    std::istream &operator>>(std::istream &is, DelimiterIO&& dest);
    std::istream &operator>>(std::istream &is, DoubleIO&& dest);
    std::istream &operator>>(std::istream &is, ComplexIO&& dest);
    std::istream &operator>>(std::istream &is, RationalIO&& dest);
    std::istream &operator>>(std::istream &is, StringIO&& dest);
    std::istream &operator>>(std::istream &is, LabelIO&& dest);
    std::istream &operator>>(std::istream &is, DataStruct& dest);
    std::ostream &operator<<(std::ostream &os, const DataStruct& d);
}

#endif
