#include "data_struct.hpp"
#include <sstream>
#include <iomanip>
#include <algorithm>
#include "iofmtguard.hpp"

std::istream& operator>>(std::istream& is, DataStruct& data) {
    std::string line;
    std::getline(is, line);
    if (line.empty()) {
        is.setstate(std::ios::failbit);
        return is;
    }

    unsigned long long temp_key1 = 0;
    std::pair<long long, unsigned long long> temp_key2 = {0, 1};
    std::string temp_key3;
    bool found_key1 = false, found_key2 = false, found_key3 = false;

    // Поиск key1
    size_t pos_key1 = line.find(":key1 ");
    if (pos_key1 != std::string::npos) {
        size_t start = pos_key1 + 6;
        size_t end = line.find(":", start);
        if (end != std::string::npos) {
            std::string hex_str = line.substr(start, end - start);
            std::stringstream ss(hex_str);
            ss >> std::hex >> temp_key1;
            if (!ss.fail()) found_key1 = true;
        }
    }

    // Поиск key2 
    size_t pos_key2 = line.find(":key2 ");
    if (pos_key2 != std::string::npos) {
        size_t start = line.find("(", pos_key2);
        size_t end = line.find(")", start);
        if (start != std::string::npos && end != std::string::npos) {
            std::string content = line.substr(start + 1, end - start - 1);
            size_t n_pos = content.find(":N");
            size_t d_pos = content.find(":D");
            if (n_pos != std::string::npos && d_pos != std::string::npos) {
                // Числитель
                std::string num_str = content.substr(n_pos + 2, d_pos - n_pos - 2);
                // Знаменатель
                std::string den_str = content.substr(d_pos + 2);
                // Удаляем пробелы
                num_str.erase(0, num_str.find_first_not_of(" \t"));
                num_str.erase(num_str.find_last_not_of(" \t") + 1);
                den_str.erase(0, den_str.find_first_not_of(" \t"));
                den_str.erase(den_str.find_last_not_of(" \t") + 1);
                try {
                    long long numerator = std::stoll(num_str);
                    unsigned long long denominator = std::stoull(den_str);
                    if (denominator != 0) {
                        temp_key2 = {numerator, denominator};
                        found_key2 = true;
                    }
                } catch (...) {}
            }
        }
    }

    size_t pos_key3 = line.find(":key3 ");
    if (pos_key3 != std::string::npos) {
        size_t quote1 = line.find("\"", pos_key3);
        if (quote1 != std::string::npos) {
            size_t quote2 = line.find("\"", quote1 + 1);
            if (quote2 != std::string::npos) {
                temp_key3 = line.substr(quote1 + 1, quote2 - quote1 - 1);
                found_key3 = true;
            }
        }
    }

    if (found_key1 && found_key2 && found_key3) {
        data.key1 = temp_key1;
        data.key2 = temp_key2;
        data.key3 = temp_key3;
    } else {
        is.setstate(std::ios::failbit);
    }

    return is;
}


std::ostream& operator<<(std::ostream& os, const DataStruct& data) {
    iofmtguard guard(os);
    os << "(:key1 0x" << std::hex << std::uppercase << data.key1;
    os << std::dec;
    os << ":key2 (:N " << data.key2.first << ":D " << data.key2.second << "):";
    os << ":key3 \"" << data.key3 << "\":)";

    return os;
}

