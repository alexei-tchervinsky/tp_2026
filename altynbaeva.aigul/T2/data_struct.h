#ifndef DATA_STRUCT_H
#define DATA_STRUCT_H

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

struct DataStruct {
    char key1;
    unsigned long long key2;
    std::string key3;
};

inline std::istream& operator>>(std::istream& in, DataStruct& data) {
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
            if (keyValue.size() == 3 && keyValue[0] == '\'' && keyValue[2] == '\'') {
                k1 = keyValue[1];
                hasKey1 = true;
            }
            else {
                in.setstate(std::ios::failbit);
                return in;
            }
        }
        else if (keyName == "key2") {
            if (keyValue.size() > 2 && keyValue[0] == '0' && (keyValue[1] == 'x' || keyValue[1] == 'X')) {
                k2 = 0;
                for (size_t i = 2; i < keyValue.size(); ++i) {
                    char c = keyValue[i];
                    if (c >= '0' && c <= '9') k2 = k2 * 16 + (c - '0');
                    else if (c >= 'A' && c <= 'F') k2 = k2 * 16 + (c - 'A' + 10);
                    else if (c >= 'a' && c <= 'f') k2 = k2 * 16 + (c - 'a' + 10);
                    else { in.setstate(std::ios::failbit); return in; }
                }
                hasKey2 = true;
            }
            else {
                in.setstate(std::ios::failbit);
                return in;
            }
        }
        else if (keyName == "key3") {
            if (keyValue.size() >= 2 && keyValue[0] == '"' && keyValue[keyValue.size() - 1] == '"') {
                k3 = keyValue.substr(1, keyValue.size() - 2);
                hasKey3 = true;
            }
            else {
                in.setstate(std::ios::failbit);
                return in;
            }
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

inline std::ostream& operator<<(std::ostream& out, const DataStruct& data) {
    out << "(:key1 '" << data.key1 << "':key2 0x" << std::hex << std::uppercase << data.key2 << std::dec << std::nouppercase << ":key3 \"" << data.key3 << "\":)";
    return out;
}

inline bool comparator(const DataStruct& a, const DataStruct& b) {
    if (a.key1 != b.key1) return a.key1 < b.key1;
    if (a.key2 != b.key2) return a.key2 < b.key2;
    return a.key3.size() < b.key3.size();
}

#endif