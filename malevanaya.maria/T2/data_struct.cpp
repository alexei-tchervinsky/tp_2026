#include "data_struct.hpp"
#include "iofmtguard.hpp"
#include <iostream>
#include <cmath>
#include <limits>

struct DelimiterIO {
    char exp;
};

std::istream& operator>>(std::istream& in, DelimiterIO&& dest) {
    std::istream::sentry sentry(in);
    if (!sentry) return in;
    char c = '0';
    in >> c;
    if (in && (c != dest.exp)) {
        in.setstate(std::ios::failbit);
    }
    return in;
}

struct DelimiterNoSkipIO {
    char exp;
};

std::istream& operator>>(std::istream& in, DelimiterNoSkipIO&& dest) {
    if (!in) return in;
    char c = '0';
    in.get(c);
    if (in && (c != dest.exp)) {
        in.setstate(std::ios::failbit);
    }
    return in;
}

static void skipToRecordEnd(std::istream& in) {
    char c = '\0';
    while (in.get(c)) {
        if (c == ':') {
            char next = '\0';
            if (in.get(next)) {
                if (next == ')') return;
                in.putback(next);
            }
        }
    }
}

static bool readRecord(std::istream& in, DataStruct& input) {
    in >> DelimiterIO{ '(' } >> DelimiterIO{ ':' };

    for (int i = 0; i < 3; ++i) {
        in >> std::ws;
        std::string key;
        char c = '\0';
        while (in.get(c) && c != ' ' && c != ':' && c != '\n') {
            key += c;
        }
        if (!in || c != ' ') {
            in.setstate(std::ios::failbit);
            return false;
        }

        if (key == "key1") {
            in >> DelimiterIO{ '\'' };
            in.get(c);
            if (!in) return false;
            input.key1 = c;
            in >> DelimiterIO{ '\'' } >> DelimiterIO{ ':' };
        }
        else if (key == "key2") {
            double r = 0.0, im = 0.0;
            in >> DelimiterIO{ '#' } >> DelimiterNoSkipIO{ 'c' } >> DelimiterNoSkipIO{ '(' }
            >> r >> im >> DelimiterIO{ ')' } >> DelimiterIO{ ':' };
            input.key2 = std::complex<double>(r, im);
        }
        else if (key == "key3") {
            in >> DelimiterIO{ '"' };
            std::getline(in, input.key3, '"');
            in >> DelimiterIO{ ':' };
        }
        else {
            in.setstate(std::ios::failbit);
            return false;
        }
    }
    in >> DelimiterIO{ ')' };
    return static_cast<bool>(in);
}

std::istream& operator>>(std::istream& in, DataStruct& dest) {
    while (in) {
        std::istream::sentry sentry(in);
        if (!sentry) break;

        DataStruct input{};
        if (readRecord(in, input)) {
            dest = input;
            return in;
        }
        in.clear();
        skipToRecordEnd(in);
    }
    return in;
}

std::ostream& operator<<(std::ostream& out, const DataStruct& src) {
    std::ostream::sentry sentry(out);
    if (!sentry) return out;
    iofmtguard fmtguard(out);

    out << "(:key1 '" << src.key1 << "':key2 #c("
        << std::fixed << std::setprecision(1)
        << src.key2.real() << " " << src.key2.imag()
        << "):key3 \"" << src.key3 << "\":)";
    return out;
}

bool compareDataStruct(const DataStruct& a, const DataStruct& b) {
    if (a.key1 != b.key1) {
        return a.key1 < b.key1;
    }
    double absA = std::abs(a.key2);
    double absB = std::abs(b.key2);
    if (absA < absB) return true;
    if (absA > absB) return false;
    return a.key3.length() < b.key3.length();
}
