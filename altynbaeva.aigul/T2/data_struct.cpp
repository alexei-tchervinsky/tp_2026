#include "data_struct.hpp"
#include <cctype>
#include <string>

std::istream& operator>>(std::istream& is, DataStruct& ds) {
    char ch;
    // Ищем начало валидной записи "(:", игнорируя любой мусор до неё
    while (is.get(ch)) {
        if (ch == '(') {
            char next_ch;
            if (is.get(next_ch)) {
                if (next_ch == ':') {
                    bool has_key1 = false, has_key2 = false, has_key3 = false;
                    bool valid = true;

                    while (is.get(ch)) {
                        if (std::isspace(static_cast<unsigned char>(ch))) continue;

                        if (ch == ':') {
                            if (!is.get(ch)) { valid = false; break; }
                            if (ch == ')') {
                                break; // Конец валидной записи
                            }

                            std::string key;
                            while (is.get(ch) && ch != ' ' && ch != ':') {
                                key += ch;
                            }
                            if (ch != ' ') { valid = false; break; }

                            if (key == "key1") {
                                if (!is.get(ch) || ch != '\'') { valid = false; break; }
                                char val;
                                if (!is.get(val)) { valid = false; break; }
                                if (!is.get(ch) || ch != '\'') { valid = false; break; }
                                if (!is.get(ch) || ch != ':') { valid = false; break; }
                                ds.key1 = val;
                                has_key1 = true;
                            }
                            else if (key == "key2") {
                                std::string hex_str;
                                while (is.get(ch) && ch != ':') {
                                    hex_str += ch;
                                }
                                if (ch != ':') { valid = false; break; }
                                try {
                                    size_t pos;
                                    ds.key2 = std::stoull(hex_str, &pos, 16);
                                    if (pos != hex_str.length()) { valid = false; break; }
                                }
                                catch (...) {
                                    valid = false; break;
                                }
                                has_key2 = true;
                            }
                            else if (key == "key3") {
                                if (!is.get(ch) || ch != '"') { valid = false; break; }
                                std::string val;
                                while (is.get(ch) && ch != '"') {
                                    val += ch;
                                }
                                if (ch != '"') { valid = false; break; }
                                if (!is.get(ch) || ch != ':') { valid = false; break; }
                                ds.key3 = val;
                                has_key3 = true;
                            }
                            else {
                                valid = false; break;
                            }
                        }
                        else {
                            valid = false; break;
                        }
                    }

                    // Если запись распарсена полностью и содержит все 3 ключа, возвращаем поток
                    if (valid && has_key1 && has_key2 && has_key3) {
                        return is;
                    }
                    // Если запись невалидна, цикл продолжится, ища следующую "(:", 
                    // что позволяет игнорировать ошибочные строки без поломки std::cin
                }
            }
        }
    }
    is.setstate(std::ios::eofbit);
    return is;
}

std::ostream& operator<<(std::ostream& os, const DataStruct& ds) {
    // 0x выводится вручную в нижнем регистре, а std::uppercase делает цифры A-F заглавными
    os << "(:key1 '" << ds.key1 << "':key2 0x"
        << std::hex << std::uppercase << ds.key2 << std::nouppercase << std::dec
        << ":key3 \"" << ds.key3 << "\":)";
    return os;
}

bool compareDataStruct(const DataStruct& a, const DataStruct& b) {
    if (a.key1 != b.key1) {
        return a.key1 < b.key1;
    }
    if (a.key2 != b.key2) {
        return a.key2 < b.key2;
    }
    return a.key3.length() < b.key3.length();
}