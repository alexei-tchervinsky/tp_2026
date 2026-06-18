#include <ostream>
#include <cmath>
#include <iomanip>

#include "datastruct.hpp"
#include "iofmtguard.hpp"

bool ds::DataStruct::operator<(DataStruct const &other) const {
    double m1 = std::abs(key1);
    double m2 = std::abs(other.key1);
    if (std::abs(m1 - m2) > 1e-9)
        return m1 < m2;

    if (key2.first * static_cast<long long>(other.key2.second) !=
        other.key2.first * static_cast<long long>(key2.second)) {
        return key2.first * static_cast<long long>(other.key2.second) <
               other.key2.first * static_cast<long long>(key2.second);
    }

    return key3.length() < other.key3.length();
}

std::istream & ds::operator>>(std::istream &is, DelimiterIO &&dest) {
    std::istream::sentry sentry(is);
    if (!sentry) return is;
    char c = '0';
    is >> c;
    if (is && (c != dest.exp)) is.setstate(std::ios::failbit);
    return is;
}

std::istream & ds::operator>>(std::istream &is, DoubleIO &&dest) {
    std::istream::sentry sentry(is);
    if (!sentry) return is;
    return is >> dest.ref;
}

std::istream & ds::operator>>(std::istream &is, ComplexIO &&dest) {
    std::istream::sentry sentry(is);
    if (!sentry) return is;
    double re = 0.0, im = 0.0;
    is >> LabelIO{"#c("} >> re >> im >> DelimiterIO{')'};
    if (is) dest.ref = {re, im};
    return is;
}

std::istream & ds::operator>>(std::istream &is, RationalIO &&dest) {
    std::istream::sentry sentry(is);
    if (!sentry) return is;
    return is >> DelimiterIO{'('}
        >> LabelIO{":N"} >> dest.ref.first
        >> LabelIO{":D"} >> dest.ref.second
        >> LabelIO{":)"};
}

std::istream & ds::operator>>(std::istream &is, StringIO &&dest) {
    std::istream::sentry sentry(is);
    if (!sentry) return is;
    return is >> std::quoted(dest.ref);
}

std::istream & ds::operator>>(std::istream &is, LabelIO &&dest) {
    std::istream::sentry sentry(is);
    if (!sentry) return is;

    for (char expected_char : dest.exp) {
        char c;
        if (!(is >> c) || (c != expected_char)) {
            is.setstate(std::ios::failbit);
            break;
        }
    }
    return is;
}

std::istream & ds::operator>>(std::istream &is, DataStruct &dest) {
    std::istream::sentry sentry(is);
    if (!sentry) return is;

    DataStruct input;
    bool keys_read[3] = {false, false, false};

    is >> DelimiterIO{'('};
    for (std::size_t i = 0; i < 3; ++i) {
        std::string key;
        is >> LabelIO{":"};
        is >> key;

        if (key == "key1") {
            is >> ComplexIO{input.key1};
            keys_read[0] = true;
        } else if (key == "key2") {
            is >> RationalIO{input.key2};
            keys_read[1] = true;
        } else if (key == "key3") {
            is >> StringIO{input.key3};
            keys_read[2] = true;
        } else {
            is.setstate(std::ios::failbit);
        }
    }
    is >> LabelIO{":)"};

    if (is && keys_read[0] && keys_read[1] && keys_read[2]) {
        dest = std::move(input);
    }
    return is;
}

std::ostream & ds::operator<<(std::ostream &os, const DataStruct &obj) {
    std::ostream::sentry sentry(os);
    if (!sentry) return os;
    iofmtguard fmtguard(os);
    // format: (:key1 #c(X X):key2 (:N X:D X):key3 "XXX":)
    return os << "("
        << ":key1 #c(" << obj.key1.real() << " " << obj.key1.imag() << ")"
        << ":key2 (:N " << obj.key2.first << ":D " << obj.key2.second << ")"
        << ":key3 \"" << obj.key3 << "\":"
        << ")";
}
