#include "data_struct.hpp"
#include "iofmtguard.hpp"
#include <iomanip>
#include <sstream>

namespace kabishev {

struct DelimiterIO {
    char exp;
};

struct HexUllIO {
    unsigned long long& ref;
};

struct RatLspIO {
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

std::istream& operator>>(std::istream& in, HexUllIO&& dest) {
    std::istream::sentry guard(in);
    if (!guard) return in;
    char c1 = 0, c2 = 0;
    in >> c1 >> c2;
    if (c1 != '0' || (c2 != 'x' && c2 != 'X')) {
        in.setstate(std::ios::ios_base::failbit);
        return in;
    }
    in >> std::hex >> dest.ref;
    return in;
}

std::istream& operator>>(std::istream& in, RatLspIO&& dest) {
    std::istream::sentry guard(in);
    if (!guard) return in;
    char labelN = 0, labelD = 0;

    in >> DelimiterIO{'('} >> DelimiterIO{':'} >> labelN;
    if (labelN != 'N') { in.setstate(std::ios::failbit); return in; }
    in >> dest.ref.first;

    in >> DelimiterIO{':'} >> labelD;
    if (labelD != 'D') { in.setstate(std::ios::failbit); return in; }
    in >> dest.ref.second;

    in >> DelimiterIO{':'} >> DelimiterIO{')'};
    return in;
}

std::istream& operator>>(std::istream& in, StringIO&& dest) {
    std::istream::sentry guard(in);
    if (!guard) return in;
    return std::getline(in >> DelimiterIO{'"'}, dest.ref, '"');
}

bool parseLine(const std::string& line, DataStruct& dest) {
    std::stringstream ss(line);
    ss >> DelimiterIO{'('};

    for (int i = 0; i < 3; ++i) {
        std::string label;
        ss >> DelimiterIO{':'} >> label;
        if (label == "key1") {
            ss >> HexUllIO{dest.key1};
        } else if (label == "key2") {
            ss >> RatLspIO{dest.key2};
        } else if (label == "key3") {
            ss >> StringIO{dest.key3};
        } else {
            return false;
        }
    }
    ss >> DelimiterIO{':'} >> DelimiterIO{')'};
    return !ss.fail();
}

std::istream& operator>>(std::istream& in, DataStruct& input) {
    std::istream::sentry guard(in);
    if (!guard) return in;

    std::string line;
    while (std::getline(in, line)) {
        if (line.empty()) continue;
        DataStruct temp;
        if (parseLine(line, temp)) {
            input = temp;
            return in;
        }
    }
    in.setstate(std::ios::failbit);
    return in;
}

std::ostream& operator<<(std::ostream& out, const DataStruct& src) {
    std::ostream::sentry guard(out);
    if (!guard) return out;
    iofmtguard fmtguard(out);

    out << "(:key1 0x" << std::uppercase << std::hex << src.key1 << std::nouppercase << std::dec;
    out << ":key2 (:N " << src.key2.first << ":D " << src.key2.second << ":)";
    out << ":key3 \"" << src.key3 << "\":)";
    return out;
}

bool compareDataStruct(const DataStruct& a, const DataStruct& b) {
    if (a.key1 != b.key1) {
        return a.key1 < b.key1;
    }
    long long valA = a.key2.first * static_cast<long long>(b.key2.second);
    long long valB = b.key2.first * static_cast<long long>(a.key2.second);
    if (valA != valB) {
        return valA < valB;
    }
    return a.key3.length() < b.key3.length();
}

}
