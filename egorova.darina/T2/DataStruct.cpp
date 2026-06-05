#include "DataStruct.hpp"
#include <iomanip>
#include <limits>

std::istream& operator>>(std::istream& in, DelimiterIO&& dest) {
    std::istream::sentry sentry(in);
    if (!sentry) return in;
    char c = ' ';
    in >> c;
    if (in && (c != dest.exp)) {
        in.setstate(std::ios::failbit);
    }
    return in;
}

std::istream& operator>>(std::istream& in, LabelIO&& dest) {
    std::istream::sentry sentry(in);
    if (!sentry) return in;
    for (char exp_c : dest.exp) {
        char c;
        if (!(in >> c) || (c != exp_c)) {
            in.setstate(std::ios::failbit);
            break;
        }
    }
    return in;
}

std::istream& operator>>(std::istream& in, DataStruct& dest) {
    std::istream::sentry sentry(in);
    if (!sentry) return in;

    DataStruct input;
    if (!(in >> DelimiterIO{'('})) return in;
    
    bool k1 = false, k2 = false, k3 = false;
    for (int i = 0; i < 3; ++i) {
        if (!(in >> DelimiterIO{':'})) return in;
        std::string key;
        char k, e, y, n;
        if (!(in >> k >> e >> y >> n)) return in;
        
        if (n == '1') {
            double re, im;
            if (!(in >> LabelIO{"#c("} >> re >> im >> DelimiterIO{')'})) return in;
            input.key1 = {re, im};
            k1 = true;
        } else if (n == '2') {
            char val;
            if (!(in >> DelimiterIO{'\''} >> val >> DelimiterIO{'\''})) return in;
            input.key2 = val;
            k2 = true;
        } else if (n == '3') {
            if (!(in >> DelimiterIO{'"'})) return in;
            std::getline(in, input.key3, '"');
            k3 = true;
        }
    }
    
    if (!(in >> DelimiterIO{':'} >> DelimiterIO{')'})) return in;
    
    if (in && k1 && k2 && k3) {
        dest = input;
    }
    return in;
}

std::ostream& operator<<(std::ostream& out, const DataStruct& src) {
    std::ostream::sentry sentry(out);
    if (!sentry) return out;
    std::streamsize precision = out.precision();
    out << std::fixed << std::setprecision(1);
    out << "(:key1 #c(" << src.key1.real() << " " << src.key1.imag() << ")";
    out << ":key2 '" << src.key2 << "'";
    out << ":key3 \"" << src.key3 << "\"";
    out << ":)";
    out.precision(precision);
    return out;
}

bool compareDataStruct(const DataStruct& a, const DataStruct& b) {
    if (std::abs(a.key1) != std::abs(b.key1)) {
        return std::abs(a.key1) < std::abs(b.key1);
    }
    if (a.key2 != b.key2) {
        return a.key2 < b.key2;
    }
    return a.key3.length() < b.key3.length();
}
