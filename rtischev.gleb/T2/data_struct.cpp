#include "data_struct.hpp"
#include <sstream>
#include <iomanip>
#include <algorithm>
#include "iofmtguard.hpp"

std::istream& operator>>(std::istream& is, DataStruct& data) {
    std::string line;

    std::getline(is, line, ')');
    line += ')';

    std::string rest;
    std::getline(is, rest, ')');
    line += rest;
    line += ')';

    unsigned long long temp_key1 = 0;
    std::pair<long long, unsigned long long> temp_key2 = {0, 1};
    std::string temp_key3;

    bool found_key1 = false;
    bool found_key2 = false;
    bool found_key3 = false;

    size_t pos_key1 = line.find(":key1 ");
    if (pos_key1 != std::string::npos) {
        size_t start = pos_key1 + 6;
        size_t end = line.find(":", start);
        if (end != std::string::npos) {

            std::string hex_str = line.substr(start, end - start);
            std::stringstream ss(hex_str);
            ss >> std::hex >> temp_key1;
            if (!ss.fail()) {
                found_key1 = true;
            }
        }
    }

    size_t key2_pos = line.find(":key2 ");
    if (key2_pos != std::string::npos) {
        size_t value_start = key2_pos + 6;

        size_t open_paren = line.find("(", value_start);
        if (open_paren != std::string::npos) {

            size_t close_paren = line.find(")", open_paren);
            if (close_paren != std::string::npos) {

                std::string rat_content = line.substr(open_paren + 1, close_paren - open_paren - 1);

                size_t n_pos = rat_content.find(":N");
                size_t d_pos = rat_content.find(":D");

                if (n_pos != std::string::npos && d_pos != std::string::npos) {
                    size_t num_start = n_pos + 2;
                    std::string num_str = rat_content.substr(num_start, d_pos - num_start);


                    num_str.erase(0, num_str.find_first_not_of(" \t"));
                    num_str.erase(num_str.find_last_not_of(" \t") + 1);

                    size_t den_start = d_pos + 2;
                    std::string den_str = rat_content.substr(den_start);
                    den_str.erase(0, den_str.find_first_not_of(" \t"));
                    den_str.erase(den_str.find_last_not_of(" \t") + 1);

                    try {
                        long long numerator = std::stoll(num_str);
                        unsigned long long denominator = std::stoull(den_str);

                        if (denominator != 0) {
                            temp_key2 = {numerator, denominator};
                            found_key2 = true;
                        }
                    } catch (...) {
                    }
                }
            }
        }
    }

    size_t pos_key3 = line.find(":key3 ");

    if (pos_key3 != std::string::npos) {
        size_t start_quote = line.find("\"", pos_key3 + 6);
        if (start_quote != std::string::npos) {
            size_t end_quote = line.find("\"", start_quote + 1);
            if (end_quote != std::string::npos) {
                temp_key3 = line.substr(start_quote + 1, end_quote - start_quote - 1);
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
    os << ":key2 (:N " << data.key2.first << ":D " << data.key2.second << ":):";
    os << "key3 \"" << data.key3 << "\":)";

    return os;
}
