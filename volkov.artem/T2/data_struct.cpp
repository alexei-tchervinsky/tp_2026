#include "data_struct.hpp"
#include "iofmtguard.hpp"

#include <cctype>
#include <iomanip>
#include <iostream>
#include <stdexcept>

namespace nspace {
    std::istream &operator>>(std::istream &in, DelimiterIO &&dest) {
        std::istream::sentry sentry(in);
        if (!sentry) {
            return in;
        }
        char c = 0;
        in >> c;
        if (in && c != dest.exp) {
            in.setstate(std::ios::failbit);
        }
        return in;
    }

    std::istream &operator>>(std::istream &in, DoubleLitIO &&dest) {
        std::istream::sentry sentry(in);
        if (!sentry) {
            return in;
        }

        std::string number = "";
        int c = in.peek();
        if (c == '+' || c == '-') {
            number += static_cast<char>(in.get());
        }

        bool before = false;
        while (std::isdigit(in.peek())) {
            before = true;
            number += static_cast<char>(in.get());
        }

        if (in.peek() != '.') {
            in.setstate(std::ios::failbit);
            return in;
        }
        number += static_cast<char>(in.get());

        bool after = false;
        while (std::isdigit(in.peek())) {
            after = true;
            number += static_cast<char>(in.get());
        }

        c = in.get();
        if (!before || !after || (c != 'd' && c != 'D')) {
            in.setstate(std::ios::failbit);
            return in;
        }

        try {
            dest.ref = std::stod(number);
        } catch (const std::exception &) {
            in.setstate(std::ios::failbit);
        }
        return in;
    }

    std::istream &operator>>(std::istream &in, CharLitIO &&dest) {
        std::istream::sentry sentry(in);
        if (!sentry) {
            return in;
        }
        char first = 0;
        char second = 0;
        char third = 0;
        in >> first >> second >> third;
        if (in && (first != '\'' || third != '\'')) {
            in.setstate(std::ios::failbit);
            return in;
        }
        dest.ref = second;
        return in;
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

        DataStruct input;
        bool key1 = false;
        bool key2 = false;
        bool key3 = false;

        in >> DelimiterIO{'('};
        for (int i = 0; i < 3 && in; ++i) {
            std::string name = "";
            in >> DelimiterIO{':'} >> name;
            if (name == "key1" && !key1) {
                in >> DoubleLitIO{input.key1};
                key1 = static_cast<bool>(in);
            } else if (name == "key2" && !key2) {
                in >> CharLitIO{input.key2};
                key2 = static_cast<bool>(in);
            } else if (name == "key3" && !key3) {
                in >> StringIO{input.key3};
                key3 = static_cast<bool>(in);
            } else {
                in.setstate(std::ios::failbit);
            }
        }
        in >> DelimiterIO{':'} >> DelimiterIO{')'};

        if (in && key1 && key2 && key3) {
            dest = input;
        } else {
            in.setstate(std::ios::failbit);
        }
        return in;
    }

    std::ostream &operator<<(std::ostream &out, const DataStruct &dest) {
        std::ostream::sentry sentry(out);
        if (!sentry) {
            return out;
        }
        iofmtguard guard(out);
        out << "(:";
        out << "key1 " << std::fixed << std::setprecision(1) << dest.key1 << "d:";
        out << "key2 '" << dest.key2 << "':";
        out << "key3 \"" << dest.key3 << "\":";
        out << ")";
        return out;
    }

    bool operator<(const DataStruct &left, const DataStruct &right) {
        if (left.key1 != right.key1) {
            return left.key1 < right.key1;
        }
        if (left.key2 != right.key2) {
            return left.key2 < right.key2;
        }
        return left.key3.size() < right.key3.size();
    }
}
