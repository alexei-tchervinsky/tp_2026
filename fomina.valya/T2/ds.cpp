#include "ds.hpp"
#include "iofmtguard.hpp"
#include <sstream>
#include <iomanip>
#include <cctype>

bool parseULLHex(const std::string& s, unsigned long long& value) {
    if (s.size() < 3 || s[0] != '0' || (s[1] != 'x' && s[1] != 'X')) return false;
    try {
        size_t pos;
        value = std::stoull(s, &pos, 16);
        return pos == s.size();
    } catch (...) {
        return false;
    }
}

bool parseDoubleLit(const std::string& s, double& value) {
    if (s.empty()) return false;
    std::string temp = s;
    if (!temp.empty() && (temp.back() == 'd' || temp.back() == 'D')) {
        temp.pop_back();
    }

    size_t dotPos = temp.find('.');
    if (dotPos == std::string::npos) return false;

    bool hasDigitBefore = false;
    for (size_t i = 0; i < dotPos; ++i) {
        if (std::isdigit(static_cast<unsigned char>(temp[i]))) {
            hasDigitBefore = true;
            break;
        }
    }
    if (!hasDigitBefore) return false;

    bool hasDigitAfter = false;
    for (size_t i = dotPos + 1; i < temp.length(); ++i) {
        if (std::isdigit(static_cast<unsigned char>(temp[i]))) {
            hasDigitAfter = true;
            break;
        }
    }
    if (!hasDigitAfter) return false;

    try {
        size_t pos;
        value = std::stod(temp, &pos);
        return pos == temp.length();
    } catch (...) {
        return false;
    }
}

std::istream& operator>>(std::istream& in, DataStruct& data) {
    std::string line;
    while (std::getline(in, line)) {
        size_t start = line.find('(');
        size_t end = line.rfind(')');
        if (start == std::string::npos || end == std::string::npos || end <= start) continue;

        std::string content = line.substr(start + 1, end - start - 1);

        auto extractValue = [&](const std::string& key, std::string& outVal) -> bool {
            std::string target = ":" + key + " ";
            size_t pos = content.find(target);
            if (pos == std::string::npos) {
                target = ":" + key;
                pos = content.find(target);
                if (pos == std::string::npos) return false;
                pos += target.length();
            } else {
                pos += target.length();
            }
            if (pos >= content.length()) return false;

            if (content[pos] == '"') {
                size_t endQuote = content.find('"', pos + 1);
                if (endQuote == std::string::npos) return false;
                outVal = content.substr(pos, endQuote - pos + 1);
                return true;
            } else {
                size_t endColon = content.find(':', pos);
                if (endColon == std::string::npos) endColon = content.length();
                outVal = content.substr(pos, endColon - pos);
                size_t valStart = outVal.find_first_not_of(" \t\r\n");
                if (valStart == std::string::npos) {
                    outVal = "";
                } else {
                    size_t valEnd = outVal.find_last_not_of(" \t\r\n");
                    outVal = outVal.substr(valStart, valEnd - valStart + 1);
                }
                return true;
            }
        };

        std::string k1_str, k2_str, k3_str;
        if (extractValue("key1", k1_str) && extractValue("key2", k2_str) && extractValue("key3", k3_str)) {
            unsigned long long k1 = 0;
            double k2 = 0;
            if (parseULLHex(k1_str, k1) && parseDoubleLit(k2_str, k2)) {
                if (k3_str.size() >= 2 && k3_str.front() == '"' && k3_str.back() == '"') {
                    data.key1 = k1;
                    data.key2 = k2;
                    data.key3 = k3_str.substr(1, k3_str.size() - 2);
                    return in;
                }
            }
        }
    }
    return in;
}

std::ostream& operator<<(std::ostream& out, const DataStruct& data) {
    iofmtguard guard(out);
    out << "(:key1 0x" << std::uppercase << std::hex << data.key1 << std::nouppercase << std::dec;
    out << ":key2 " << std::fixed << std::setprecision(1) << data.key2 << 'd';
    out << ":key3 \"" << data.key3 << "\":)";
    return out;
}

bool comparator(const DataStruct& a, const DataStruct& b) {
    if (a.key1 != b.key1) return a.key1 < b.key1;
    if (a.key2 != b.key2) return a.key2 < b.key2;
    return a.key3.length() < b.key3.length();
}
