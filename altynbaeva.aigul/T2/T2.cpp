#include "data_struct.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <string>
#include <iomanip>
#include <cctype>

char parseKey1(const std::string& s) {
    if (s.size() == 3 && s[0] == '\'' && s[2] == '\'') {
        return s[1];
    }

    if (s.find('.') != std::string::npos || s.find('e') != std::string::npos || s.find('E') != std::string::npos) {
        try {
            double d = std::stod(s);
            return static_cast<char>(d);
        } catch(...) {}
    }

    try {
        long long ll = std::stoll(s);
        return static_cast<char>(ll);
    } catch(...) {}

    return 0;
}

unsigned long long parseKey2(const std::string& s) {
    unsigned long long result = 0;
    std::string str = s;

    if (str.size() >= 3 && (str.substr(str.size()-3) == "ULL" || str.substr(str.size()-3) == "ull")) {
        str = str.substr(0, str.size()-3);
    } else if (str.size() >= 1 && (str.back() == 'u' || str.back() == 'U')) {
        str.pop_back();
    }

    if (str.size() > 2 && str[0] == '0' && (str[1] == 'x' || str[1] == 'X')) {
        result = std::stoull(str.substr(2), nullptr, 16);
    }
    else if (str.size() > 2 && str[0] == '0' && (str[1] == 'b' || str[1] == 'B')) {
        result = std::stoull(str.substr(2), nullptr, 2);
    }
    else if (str.size() > 1 && str[0] == '0' && (str[1] >= '0' && str[1] <= '7')) {
        result = std::stoull(str, nullptr, 8);
    }
    else {
        try {
            result = std::stoull(str);
        } catch(...) { return 0; }
    }

    return result;
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
    char k1 = 0;
    unsigned long long k2 = 0;
    std::string k3;

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
            k1 = parseKey1(keyValue);
            hasKey1 = true;
        } else if (keyName == "key2") {
            k2 = parseKey2(keyValue);
            hasKey2 = true;
        } else if (keyName == "key3") {
            if (keyValue.size() >= 2 && keyValue[0] == '"' && keyValue.back() == '"') {
                k3 = keyValue.substr(1, keyValue.size() - 2);
                hasKey3 = true;
            }
        } else {
            in.setstate(std::ios::failbit);
            return in;
        }
    }

    if (!hasKey1 || !hasKey2 || !hasKey3) {
        in.setstate(std::ios::failbit);
        return in;
    }

    data.key1 = k1;
    data.key2 = k2;
    data.key3 = k3;
    return in;
}

std::ostream& operator<<(std::ostream& out, const DataStruct& data) {
    out << "(:key1 '" << data.key1 << "':key2 0x"
        << std::hex << std::uppercase << data.key2
        << std::dec << std::nouppercase << ":key3 \"" << data.key3 << "\":)";
    return out;
}

bool comparator(const DataStruct& a, const DataStruct& b) {
    if (a.key1 != b.key1) return a.key1 < b.key1;
    if (a.key2 != b.key2) return a.key2 < b.key2;
    return a.key3.size() < b.key3.size();
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
        std::cout << d << "\n";
    }
    return 0;
}
