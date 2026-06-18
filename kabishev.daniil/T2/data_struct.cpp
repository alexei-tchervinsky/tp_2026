#include "data_struct.hpp"
#include "iofmtguard.hpp"
#include <iomanip>

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
            in.setstate(std::ios::failbit);
            return in;
        }
        in >> std::hex >> dest.ref;
        return in;
    }

    std::istream& operator>>(std::istream& in, RatLspIO&& dest) {
        std::istream::sentry guard(in);
        if (!guard) return in;
        char c1 = 0, c2 = 0, c3 = 0, c4 = 0, c5 = 0, c6 = 0, c7 = 0;

        in >> c1 >> c2; // Ожидаем (:
        if (c1 != '(' || c2 != ':') {
            in.setstate(std::ios::failbit);
            return in;
        }

        in >> c3; // Ожидаем N
        if (c3 != 'N') {
            in.setstate(std::ios::failbit);
            return in;
        }

        in >> dest.ref.first;

        in >> c4; // Ожидаем :
        if (c4 != ':') {
            in.setstate(std::ios::failbit);
            return in;
        }

        in >> c5; // Ожидаем D
        if (c5 != 'D') {
            in.setstate(std::ios::failbit);
            return in;
        }

        in >> dest.ref.second;

        in >> c6 >> c7; // Ожидаем :)
        if (c6 != ':' || c7 != ')') {
            in.setstate(std::ios::failbit);
        }
        return in;
    }

    std::istream& operator>>(std::istream& in, StringIO&& dest) {
        std::istream::sentry guard(in);
        if (!guard) return in;
        char c = 0;
        in >> c;
        if (c != '"') {
            in.setstate(std::ios::failbit);
            return in;
        }
        std::getline(in, dest.ref, '"');
        return in;
    }

    std::istream& operator>>(std::istream& in, DataStruct& dest) {
        std::istream::sentry guard(in);
        if (!guard) return in;

        char c1 = 0, c2 = 0;
        in >> c1 >> c2; // Ожидаем начало структуры (:
        if (c1 != '(' || c2 != ':') {
            in.setstate(std::ios::failbit);
            return in;
        }

        DataStruct input{};
        bool keys_valid[3] = {false, false, false};

        for (int i = 0; i < 3; ++i) {
            std::string label;
            in >> label; // Считывает имя ключа (например, "key1", "key2", "key3")
            if (!in) break;

            if (label == "key1") {
                if (in >> HexUllIO{input.key1}) {
                    keys_valid[0] = true;
                }
            } else if (label == "key2") {
                if (in >> RatLspIO{input.key2}) {
                    keys_valid[1] = true;
                }
            } else if (label == "key3") {
                if (in >> StringIO{input.key3}) {
                    keys_valid[2] = true;
                }
            } else {
                in.setstate(std::ios::failbit);
                break;
            }

            char sep = 0;
            in >> sep; // После значения каждого ключа обязательно идет двоеточие ':'
            if (sep != ':') {
                in.setstate(std::ios::failbit);
                break;
            }
        }

        char close_bracket = 0;
        in >> close_bracket; // Ожидаем закрывающую скобку )
        if (close_bracket != ')') {
            in.setstate(std::ios::failbit);
        }

        if (in && keys_valid[0] && keys_valid[1] && keys_valid[2]) {
            dest = std::move(input);
        } else {
            in.setstate(std::ios::failbit);
        }

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
        if (a.key2 != b.key2) {
            return a.key2 < b.key2;
        }
        return a.key3.size() < b.key3.size();
    }
}
