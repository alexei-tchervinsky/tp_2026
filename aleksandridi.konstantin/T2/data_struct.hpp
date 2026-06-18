#ifndef DATA_STRUCT_HPP
#define DATA_STRUCT_HPP

#include <string>
#include <iosfwd>

namespace nspace {
    struct DataStruct {
        double key1;
        char key2;
        std::string key3;
    };

    struct DelimiterIO {
        char expected;
    };

    struct DoubleSciIO {
        double &ref;
    };

    struct CharLitIO {
        char &ref;
    };

    struct StringIO {
        std::string &ref;
    };

    std::istream &operator>>(std::istream &in, DelimiterIO &&dest);
    std::istream &operator>>(std::istream &in, DoubleSciIO &&dest);
    std::istream &operator>>(std::istream &in, CharLitIO &&dest);
    std::istream &operator>>(std::istream &in, StringIO &&dest);
    std::istream &operator>>(std::istream &in, DataStruct &dest);
    std::ostream &operator<<(std::ostream &out, const DataStruct &src);

    bool compareDataStruct(const DataStruct &lhs, const DataStruct &rhs);
}

#endif
