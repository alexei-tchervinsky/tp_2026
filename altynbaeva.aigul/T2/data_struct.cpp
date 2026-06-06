#include "data_struct.h"
#include <iostream>
#include <string>
#include <stdexcept>
#include <iomanip>
#include <cctype>

static char parseKey1(const std::string& s) {
    if (s.size() == 3 && s.front() == '\'' && s.back() == '\'') {
        return s[1];
    }
    throw std::invalid_argument("Invalid CHR LIT");
}

static unsigned long long parseKey2(const std::string& s) {
    if (s.size() < 3) throw std::invalid_argument("Too short for ULL HEX");
    if (s[0] != '0' || (s[1] != 'x' && s[1] != 'X'))
        throw std::invalid_argument("Not ULL HEX");
    for (size_t i = 2; i < s.size(); ++i) {
        if (!std::isxdigit(static_cast<unsigned char>(s[i])))
            throw std::invalid_argument("Invalid hex digit");
    }
    return std::stoull(s.substr(2), nullptr, 16);
}

std::istream& operator>>(std::istream& in, DataStruct& data) {
    std::string line;
    while (std::getline(in, line)) {
        size_t start = line.find_first_not_of(" \t\r\n");
        size_t end = line.find_last_not_of(" \t\r\n");
        if (start == std::string::npos) continue;
        line = line.substr(start, end - start + 1);

        if (line.size() < 5 || line.substr(0, 2) != "(:" || line.substr(line.size() - 2) != ":)")
            continue;

        // Убираем '(' в начале, оставляем ':key1 ...:)'
        std::string inner = line.substr(1, line.size() - 1);

        bool hasKey1 = false, hasKey2 = false, hasKey3 = false;
        char k1 = 0;
        unsigned long long k2 = 0;
        std::string k3;

        try {
            size_t pos = 0;
            while (pos < inner.size()) {
                // Проверяем, не достигли ли мы ":)" в конце
                if (pos + 1 < inner.size() && inner[pos] == ':' && inner[pos + 1] == ')') {
                    break;
                }

                if (inner[pos] != ':') throw std::invalid_argument("Expected ':'");
                pos++;

                size_t spacePos = inner.find(' ', pos);
                if (spacePos == std::string::npos) throw std::invalid_argument("No space");
                std::string keyName = inner.substr(pos, spacePos - pos);
                pos = spacePos + 1;

                std::string value;
                if (pos < inner.size() && inner[pos] == '"') {
                    pos++;
                    size_t endQuote = inner.find('"', pos);
                    if (endQuote == std::string::npos) throw std::invalid_argument("Unclosed quote");
                    value = inner.substr(pos, endQuote - pos);
                    pos = endQuote + 1;
                } else {
                    size_t colonPos = inner.find(':', pos);
                    if (colonPos == std::string::npos) throw std::invalid_argument("No closing ':'");
                    value = inner.substr(pos, colonPos - pos);
                    pos = colonPos;
                }

                if (keyName == "key1") {
                    k1 = parseKey1(value);
                    hasKey1 = true;
                } else if (keyName == "key2") {
                    k2 = parseKey2(value);
                    hasKey2 = true;
                } else if (keyName == "key3") {
                    k3 = value;
                    hasKey3 = true;
                } else {
                    throw std::invalid_argument("Unknown key");
                }
            }

            if (!hasKey1 || !hasKey2 || !hasKey3) continue;

            data.key1 = k1;
            data.key2 = k2;
            data.key3 = k3;
            return in;

        } catch (...) {
            continue;
        }
    }
    in.setstate(std::ios::eofbit | std::ios::failbit);
    return in;
}

std::ostream& operator<<(std::ostream& out, const DataStruct& data) {
    out << "(:key1 '" << data.key1 << "':key2 0x"
        << std::hex << std::uppercase << data.key2
        << std::dec << std::nouppercase
        << ":key3 \"" << data.key3 << "\":)";
    return out;
}

bool comparator(const DataStruct& a, const DataStruct& b) {
    if (a.key1 != b.key1) return a.key1 < b.key1;
    if (a.key2 != b.key2) return a.key2 < b.key2;
    return a.key3.size() < b.key3.size();
}
