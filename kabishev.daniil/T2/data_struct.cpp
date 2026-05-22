#include "data_struct.hpp"
#include <cmath>

namespace kabishev {

struct DelimiterIO {
    char exp;
};

struct CharLitIO {
    char& ref;
};

struct CmpLspIO {
    std::pair<long long, unsigned long long>& ref;
};

struct StringIO {
    std::string& ref;
};

std::istream& operator>>(std::istream& in, DelimiterIO&& dest) {
    std::istream::sentry guard(in);
    if (!guard) return in;
    char c = 0;
    in >> c;
    if (c != dest.exp) {
        in.setstate(std::ios::failbit);
    }
    return in;
}

std::istream& operator>>(std::istream& in, CharLitIO&& dest) {
    std::istream::sentry guard(in);
    if (!guard) return in;
    in >> DelimiterIO{'\''} >> dest.ref >> DelimiterIO{'\''};
    return in;
}

std::istream& operator>>(std::istream& in, CmpLspIO&& dest) {
    std::istream::sentry guard(in);
    if (!guard) return in;
    in >> DelimiterIO{'#'} >> DelimiterIO{'c'} >> DelimiterIO{'('} >> dest.ref.first >> dest.ref.second >> DelimiterIO{')'};
    return in;
}

std::istream& operator>>(std::istream& in, StringIO&& dest) {
    std::istream::sentry guard(in);
    if (!guard) return in;
    return std::getline(in >> DelimiterIO{'"'}, dest.ref, '"');
}

std::istream& operator>>(std::istream& in, DataStruct& input) {
    std::istream::sentry guard(in);
    if (!guard) return in;

    DataStruct temp;
    in >> DelimiterIO{'('};

    for (int i = 0; i < 3; ++i) {
        std::string label;
        in >> DelimiterIO{':'} >> label;
        if (label == "key1") {
            in >> CharLitIO{temp.key1};
        } else if (label == "key2") {
            in >> CmpLspIO{temp.key2};
        } else if (label == "key3") {
            in >> StringIO{temp.key3};
        } else {
            in.setstate(std::ios::failbit);
        }
    }

    in >> DelimiterIO{')'};
    if (in) {
        input = temp;
    }
    return in;
}

std::ostream& operator<<(std::ostream& out, const DataStruct& src) {
    std::ostream::sentry guard(out);
    if (!guard) return out;

    out << "(:key1 '" << src.key1
        << "':key2 #c(" << src.key2.first << " " << src.key2.second
        << "):key3 \"" << src.key3 << "\")";
    return out;
}

bool compareDataStruct(const DataStruct& a, const DataStruct& b) {
    double absA = std::sqrt(std::pow(a.key2.first, 2) + std::pow(a.key2.second, 2));
    double absB = std::sqrt(std::pow(b.key2.first, 2) + std::pow(b.key2.second, 2));
    return absA < absB;
}

}
