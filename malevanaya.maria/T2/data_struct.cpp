#include "data_struct.hpp"
#include "iofmtguard.hpp"
#include <iomanip>
#include <cmath>

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

std::istream& operator>>(std::istream& in, DelimiterNoSkipIO&& dest) {
    if (!in) return in;
    char c = '0';
    in.get(c);
    if (in && (c != dest.exp)) {
        in.setstate(std::ios::failbit);
    }
    return in;
}

std::istream& operator>>(std::istream& in, LabelIO&& dest) {
    std::istream::sentry sentry(in);
    if (!sentry) return in;
    std::string key;
    if (!(in >> key)) return in;
    if (key != dest.exp) {
        in.setstate(std::ios::failbit);
    }
    return in;
}

std::istream& operator>>(std::istream& in, CharLitIO&& dest) {
    std::istream::sentry sentry(in);
    if (!sentry) return in;
    char c = '0';
    in >> DelimiterIO{ '\'' };
    in.get(c);
    if (!in) return in;
    dest.ref = c;
    in >> DelimiterIO{ '\'' };
    return in;
}

std::istream& operator>>(std::istream& in, CmpLspIO&& dest) {
    std::istream::sentry sentry(in);
    if (!sentry) return in;
    double r = 0.0, im = 0.0;
    in >> DelimiterIO{ '#' } >> DelimiterNoSkipIO{ 'c' } >> DelimiterNoSkipIO{ '(' }
    >> r >> im >> DelimiterIO{ ')' };
    if (in) {
        dest.ref = std::complex<double>(r, im);
    }
    return in;
}

std::istream& operator>>(std::istream& in, StringIO&& dest) {
    std::istream::sentry sentry(in);
    if (!sentry) return in;
    return std::getline(in >> DelimiterIO{ '"' }, dest.ref, '"');
}

std::istream& operator>>(std::istream& in, DataStruct& dest) {
    std::istream::sentry sentry(in);
    if (!sentry) return in;

    DataStruct input;
    bool keys_valid[3]{ false, false, false };

    in >> DelimiterIO{ '(' } >> DelimiterIO{ ':' };

    for (int i = 0; i < 3; ++i) {
        std::string key;
        if (!(in >> key)) break;

        if (key == "key1") {
            in >> CharLitIO{ input.key1 } >> DelimiterIO{ ':' };
            if (in) keys_valid[0] = true;
        }
        else if (key == "key2") {
            in >> CmpLspIO{ input.key2 } >> DelimiterIO{ ':' };
            if (in) keys_valid[1] = true;
        }
        else if (key == "key3") {
            in >> StringIO{ input.key3 } >> DelimiterIO{ ':' };
            if (in) keys_valid[2] = true;
        }
        else {
            in.setstate(std::ios::failbit);
            break;
        }
    }

    in >> DelimiterIO{ ')' };

    if (in && keys_valid[0] && keys_valid[1] && keys_valid[2]) {
        dest = input;
    }
    else if (in) {
        in.setstate(std::ios::failbit);
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
