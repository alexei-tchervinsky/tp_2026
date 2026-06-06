#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <string>
#include <complex>
#include <cmath>
#include <iomanip>

struct DataStruct {
    enum Type { NONE, DOUBLE, LONG_LONG, UNSIGNED_LONG_LONG, CHAR, COMPLEX, RATIONAL };
    Type type1, type2;

    double double1, double2;
    long long ll1, ll2;
    unsigned long long ull1, ull2;
    char char1, char2;
    std::complex<double> complex1, complex2;
    std::pair<long long, unsigned long long> rational1, rational2;

    std::string key3;

    DataStruct() : type1(NONE), type2(NONE), double1(0), double2(0), ll1(0), ll2(0),
                   ull1(0), ull2(0), char1(0), char2(0) {}
};

bool parseDouble(const std::string& s, double& value) {
    std::string str = s;
    if (!str.empty() && (str.back() == 'd' || str.back() == 'D')) str.pop_back();
    size_t pos = 0;
    try {
        value = std::stod(str, &pos);
        return pos == str.size();
    } catch (...) { return false; }
}

bool parseLongLong(const std::string& s, long long& value) {
    if (s.empty()) return false;
    std::string str = s;
    if (str.size() >= 2 && (str.substr(str.size()-2) == "LL" || str.substr(str.size()-2) == "ll"))
        str = str.substr(0, str.size()-2);
    size_t pos = 0;
    try {
        value = std::stoll(str, &pos);
        return pos == str.size();
    } catch (...) { return false; }
}

bool parseUnsignedLongLong(const std::string& s, unsigned long long& value) {
    if (s.empty()) return false;
    std::string str = s;
    if (str.size() >= 3 && (str.substr(str.size()-3) == "ULL" || str.substr(str.size()-3) == "ull"))
        str = str.substr(0, str.size()-3);
    else if (!str.empty() && (str.back() == 'u' || str.back() == 'U'))
        str.pop_back();
    if (str.size() > 1 && str[0] == '0' && str[1] != 'x' && str[1] != 'X' && str[1] != 'b' && str[1] != 'B') {
        try {
            value = std::stoull(str, nullptr, 8);
            return true;
        } catch (...) { return false; }
    }
    if (str.size() > 2 && str[0] == '0' && (str[1] == 'b' || str[1] == 'B')) {
        value = 0;
        for (size_t i = 2; i < str.size(); ++i) {
            char c = str[i];
            if (c == '0') value = value * 2;
            else if (c == '1') value = value * 2 + 1;
            else return false;
        }
        return true;
    }
    if (str.size() > 2 && str[0] == '0' && (str[1] == 'x' || str[1] == 'X')) {
        try {
            value = std::stoull(str, nullptr, 16);
            return true;
        } catch (...) { return false; }
    }
    try {
        value = std::stoull(str);
        return true;
    } catch (...) { return false; }
}

bool parseChar(const std::string& s, char& value) {
    if (s.size() == 3 && s[0] == '\'' && s[2] == '\'') {
        value = s[1];
        return true;
    }
    return false;
}

bool parseComplex(const std::string& s, std::complex<double>& value) {
    if (s.size() < 6 || s.substr(0,3) != "#c(" || s.back() != ')') return false;
    std::string inner = s.substr(3, s.size() - 4);
    size_t space = inner.find(' ');
    if (space == std::string::npos) return false;
    double real, imag;
    if (!parseDouble(inner.substr(0, space), real)) return false;
    if (!parseDouble(inner.substr(space+1), imag)) return false;
    value = std::complex<double>(real, imag);
    return true;
}

bool parseRational(const std::string& s, std::pair<long long, unsigned long long>& value) {
    if (s.size() < 6 || s.substr(0,3) != "(:N" || s.back() != ':') return false;
    size_t dPos = s.find(":D");
    if (dPos == std::string::npos) return false;
    std::string numStr = s.substr(3, dPos - 3);
    std::string denStr = s.substr(dPos+2, s.size() - dPos - 3);
    long long num;
    unsigned long long den;
    if (!parseLongLong(numStr, num)) return false;
    if (!parseUnsignedLongLong(denStr, den)) return false;
    value = {num, den};
    return true;
}

std::istream& operator>>(std::istream& in, DataStruct& data) {
    std::string line;
    if (!std::getline(in, line)) return in;

    size_t start = line.find_first_not_of(" \t");
    size_t end = line.find_last_not_of(" \t");
    if (start == std::string::npos || end == std::string::npos) {
        in.setstate(std::ios::failbit);
        return in;
    }
    line = line.substr(start, end - start + 1);

    if (line.size() < 4 || line[0] != '(' || line[1] != ':' || line.back() != ':') {
        in.setstate(std::ios::failbit);
        return in;
    }

    line = line.substr(2, line.size() - 3);

    bool hasKey1 = false, hasKey2 = false, hasKey3 = false;
    DataStruct d;

    size_t pos = 0;
    while (pos < line.size()) {
        if (line[pos] != ':') {
            in.setstate(std::ios::failbit);
            return in;
        }
        pos++;
        size_t nextPos = line.find(':', pos);
        if (nextPos == std::string::npos) {
            in.setstate(std::ios::failbit);
            return in;
        }
        std::string part = line.substr(pos, nextPos - pos);
        pos = nextPos;

        size_t spacePos = part.find(' ');
        if (spacePos == std::string::npos) {
            in.setstate(std::ios::failbit);
            return in;
        }
        std::string keyName = part.substr(0, spacePos);
        std::string keyValue = part.substr(spacePos + 1);

        if (keyName == "key1") {
            if (parseChar(keyValue, d.char1)) { d.type1 = DataStruct::CHAR; hasKey1 = true; }
            else if (parseDouble(keyValue, d.double1)) { d.type1 = DataStruct::DOUBLE; hasKey1 = true; }
            else if (parseLongLong(keyValue, d.ll1)) { d.type1 = DataStruct::LONG_LONG; hasKey1 = true; }
            else if (parseUnsignedLongLong(keyValue, d.ull1)) { d.type1 = DataStruct::UNSIGNED_LONG_LONG; hasKey1 = true; }
            else if (parseComplex(keyValue, d.complex1)) { d.type1 = DataStruct::COMPLEX; hasKey1 = true; }
            else if (parseRational(keyValue, d.rational1)) { d.type1 = DataStruct::RATIONAL; hasKey1 = true; }
        }
        else if (keyName == "key2") {
            if (parseChar(keyValue, d.char2)) { d.type2 = DataStruct::CHAR; hasKey2 = true; }
            else if (parseDouble(keyValue, d.double2)) { d.type2 = DataStruct::DOUBLE; hasKey2 = true; }
            else if (parseLongLong(keyValue, d.ll2)) { d.type2 = DataStruct::LONG_LONG; hasKey2 = true; }
            else if (parseUnsignedLongLong(keyValue, d.ull2)) { d.type2 = DataStruct::UNSIGNED_LONG_LONG; hasKey2 = true; }
            else if (parseComplex(keyValue, d.complex2)) { d.type2 = DataStruct::COMPLEX; hasKey2 = true; }
            else if (parseRational(keyValue, d.rational2)) { d.type2 = DataStruct::RATIONAL; hasKey2 = true; }
        }
        else if (keyName == "key3") {
            if (keyValue.size() >= 2 && keyValue[0] == '"' && keyValue.back() == '"') {
                d.key3 = keyValue.substr(1, keyValue.size() - 2);
                hasKey3 = true;
            }
        }
    }

    if (!hasKey1 || !hasKey2 || !hasKey3) {
        in.setstate(std::ios::failbit);
        return in;
    }

    data = d;
    return in;
}

std::ostream& operator<<(std::ostream& out, const DataStruct& d) {
    out << "(:key1 ";
    switch(d.type1) {
        case DataStruct::DOUBLE: out << std::fixed << std::setprecision(1) << d.double1 << "d"; break;
        case DataStruct::LONG_LONG: out << d.ll1 << "ll"; break;
        case DataStruct::UNSIGNED_LONG_LONG:
            if (d.ull1 <= 9) out << d.ull1;
            else out << "0x" << std::hex << std::uppercase << d.ull1 << std::dec;
            break;
        case DataStruct::CHAR: out << "'" << d.char1 << "'"; break;
        case DataStruct::COMPLEX: out << "#c(" << d.complex1.real() << " " << d.complex1.imag() << ")"; break;
        case DataStruct::RATIONAL: out << "(:N" << d.rational1.first << ":D" << d.rational1.second << ":)"; break;
        default: break;
    }
    out << ":key2 ";
    switch(d.type2) {
        case DataStruct::DOUBLE: out << std::fixed << std::setprecision(1) << d.double2 << "d"; break;
        case DataStruct::LONG_LONG: out << d.ll2 << "ll"; break;
        case DataStruct::UNSIGNED_LONG_LONG:
            if (d.ull2 <= 9) out << d.ull2;
            else out << "0x" << std::hex << std::uppercase << d.ull2 << std::dec;
            break;
        case DataStruct::CHAR: out << "'" << d.char2 << "'"; break;
        case DataStruct::COMPLEX: out << "#c(" << d.complex2.real() << " " << d.complex2.imag() << ")"; break;
        case DataStruct::RATIONAL: out << "(:N" << d.rational2.first << ":D" << d.rational2.second << ":)"; break;
        default: break;
    }
    out << ":key3 \"" << d.key3 << "\":)";
    return out;
}

bool comparator(const DataStruct& a, const DataStruct& b) {
    if (a.type1 != b.type1) return a.type1 < b.type1;
    switch(a.type1) {
        case DataStruct::DOUBLE: return a.double1 < b.double1;
        case DataStruct::LONG_LONG: return a.ll1 < b.ll1;
        case DataStruct::UNSIGNED_LONG_LONG: return a.ull1 < b.ull1;
        case DataStruct::CHAR: return a.char1 < b.char1;
        case DataStruct::COMPLEX: return std::abs(a.complex1) < std::abs(b.complex1);
        case DataStruct::RATIONAL: {
            double av = static_cast<double>(a.rational1.first) / static_cast<double>(a.rational1.second);
            double bv = static_cast<double>(b.rational1.first) / static_cast<double>(b.rational1.second);
            return av < bv;
        }
        default: return false;
    }
}

int main() {
    std::vector<DataStruct> data;
    std::string line;

    while (std::getline(std::cin, line)) {
        if (line.empty()) break;
        std::istringstream iss(line);
        DataStruct d;
        if (iss >> d) {
            data.push_back(d);
        }
    }

    std::sort(data.begin(), data.end(), comparator);

    for (const auto& d : data) {
        std::cout << d << '\n';
    }

    return 0;
}
