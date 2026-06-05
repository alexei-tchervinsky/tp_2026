#include "data_struct.hpp"
#include "iofmtguard.hpp"
#include <iostream>
#include <cctype>
#include <iomanip>
#include <cmath>
#include <sstream>

namespace nspace {
    std::istream &operator>>(std::istream &in, DelimiterIO &&dest) {
        std::istream::sentry sentry(in);
        if (!sentry) {
            return in;
        }
        char c = 0;
        in >> c;
        if (in && c != dest.expected) {
            in.setstate(std::ios::failbit);
        }
        return in;
    }

    std::istream &operator>>(std::istream &in, DoubleSciIO &&dest) {
        std::istream::sentry sentry(in);
        if (!sentry) {
            return in;
        }

        std::string buffer;
        char c = 0;
        bool has_dot = false;
        bool has_exp = false;

        while (in >> c) {
            if (c == '.') {
                has_dot = true;
            } else if (c == 'e' || c == 'E') {
                has_exp = true;
            } else if (c == ':') {
                in.putback(':');
                break;
            }
            buffer += c;
        }

        if (!has_dot || !has_exp) {
            in.setstate(std::ios::failbit);
            return in;
        }

        try {
            std::size_t processed = 0;
            dest.ref = std::stod(buffer, &processed);
            if (processed != buffer.size()) {
                in.setstate(std::ios::failbit);
            }
        } catch (...) {
            in.setstate(std::ios::failbit);
        }

        return in;
    }

    std::istream &operator>>(std::istream &in, CharLitIO &&dest) {
        std::istream::sentry sentry(in);
        if (!sentry) {
            return in;
        }
        return in >> DelimiterIO{'\''} >> dest.ref >> DelimiterIO{'\''};
    }

    std::istream &operator>>(std::istream &in, StringIO &&dest) {
        std::istream::sentry sentry(in);
        if (!sentry) {
            return in;
        }
        return std::getline(in >> DelimiterIO{'"'}, dest.ref, '"');
    }

    std::istream &operator>>(std::istream &in, DataStruct &dest) {
        std::istream::sentry sentry(in);
        if (!sentry) {
            return in;
        }

        DataStruct temp;
        bool parsed_k1 = false, parsed_k2 = false, parsed_k3 = false;

        in >> DelimiterIO{'('};

        for (int i = 0; i < 3; ++i) {
            char num = 0;
            in >> DelimiterIO{':'} >> DelimiterIO{'k'} >> DelimiterIO{'e'} >> DelimiterIO{'y'} >> num;

            if (!in) {
                return in;
            }

            if (num == '1' && !parsed_k1) {
                in >> DoubleSciIO{temp.key1};
                parsed_k1 = static_cast<bool>(in);
            } else if (num == '2' && !parsed_k2) {
                in >> CharLitIO{temp.key2};
                parsed_k2 = static_cast<bool>(in);
            } else if (num == '3' && !parsed_k3) {
                in >> StringIO{temp.key3};
                parsed_k3 = static_cast<bool>(in);
            } else {
                in.setstate(std::ios::failbit);
                return in;
            }
        }

        in >> DelimiterIO{':'} >> DelimiterIO{')'};

        if (in && parsed_k1 && parsed_k2 && parsed_k3) {
            dest = temp;
        } else {
            in.setstate(std::ios::failbit);
        }
        return in;
    }

    std::ostream &operator<<(std::ostream &out, const DataStruct &src) {
        std::ostream::sentry sentry(out);
        if (!sentry) {
            return out;
        }
        iofmtguard guard(out);
        std::stringstream ss;
        ss << std::scientific << std::setprecision(1) << src.key1;
        std::string num_str = ss.str();
        std::size_t e_pos = num_str.find_first_of("eE");
        if (e_pos != std::string::npos && e_pos + 2 < num_str.size()) {
            if (num_str[e_pos + 2] == '0' && e_pos + 3 < num_str.size()) {
                num_str.erase(e_pos + 2, 1);
            }
        }
        out << "(:";
        out << "key1 " << num_str << ':';
        out << "key2 '" << src.key2 << "':";
        out << "key3 \"" << src.key3 << "\":)";
        return out;
    }

    bool compareDataStruct(const DataStruct &lhs, const DataStruct &rhs) {
        if (lhs.key1 != rhs.key1) {
            return lhs.key1 < rhs.key1;
        }
        if (lhs.key2 != rhs.key2) {
            return lhs.key2 < rhs.key2;
        }
        return lhs.key3.size() < rhs.key3.size();
    }
}
