#include <iostream>
#include <sstream>
#include <string>
#include <cassert>
#include <iterator>
#include <vector>
#include <iomanip>
#include <limits>
#include <algorithm>
#include <cmath>
namespace nspace
{
    // 7. DBL SCI SLL LIT
    /* Тесты
(:key1 5123.453424e1:key2 -89ll:key3 "Data":)
(:key2 10ll:key3 "Hello":key1 1.00e+1:)
(:key3 "ABC":key1 2.5E+0:key2 0ll:)
(:key1 1.0e+0:key2 -1ll:key3 "A":)
(:key1 1.0e+1:key2 5ll:key3 "X":)
(:key1 1.0e+1:key2 5ll:key3 "Longer":)
(:key1 5e-2:key2 10ll:key3 "Bad":)
(:key1 5.       45:key2 10ll:key3 "Bad":)
(:key1 1.0e+1:key2 10:key3 "Bad":
key1 1.0e+1:key2 10ll:key3 "OK":key4 123:)
(:key1 1.0e+1:key3 "Missing":)
hello world
    */
    struct Data
    {
        double key1;
        long long key2;
        std::string key3;
    };
    struct DelimiterIO
    {
        char exp;
    };
    struct DoubleIO
    {
        double& ref;
    };
    struct LongIO
    {
        long long& ref;
    };
    struct StringKeyIO
    {
        std::string& ref;
    };
    struct KeyIO
    {
        std::string exp;
    };
    struct StringLabelIO
    {
        std::string& ref;
    };
    struct LabelIO
    {
        std::string exp;
    };
    class iofmtguard
    {
    public:
        iofmtguard(std::basic_ios< char >& s);
        ~iofmtguard();
    private:
        std::basic_ios< char >& s_;
        std::streamsize width_;
        char fill_;
        std::streamsize precision_;
        std::basic_ios< char >::fmtflags fmt_;
    };
    std::istream& operator>>(std::istream& in, DelimiterIO&& dest);
    std::istream& operator>>(std::istream& in, DoubleIO&& dest);
    std::istream& operator>>(std::istream& in, StringKeyIO&& dest);
    std::istream& operator>>(std::istream& in, KeyIO&& dest);
    std::istream& operator>>(std::istream& in, StringLabelIO&& dest);
    std::istream& operator>>(std::istream& in, LabelIO&& dest);
    std::istream& operator>>(std::istream& in, Data& dest);
    std::ostream& operator<<(std::ostream& out, const Data& dest);
    bool comparator(const nspace::Data& a, const nspace::Data& b);
}
int main()
{
    std::vector<nspace::Data> data;
    while (!std::cin.eof()) {
        std::copy(
            std::istream_iterator<nspace::Data>(std::cin),
            std::istream_iterator<nspace::Data>(),
            std::back_inserter(data)
        );
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    std::sort(data.begin(), data.end(), nspace::comparator);
    std::copy(
        data.begin(),
        data.end(),
        std::ostream_iterator<nspace::Data>(std::cout, "\n")
    );
    return 0;
}
namespace nspace
{
    std::istream& operator>>(std::istream& in, DelimiterIO&& dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        char c = '0';
        in >> c;
        if (in && (c != dest.exp))
        {
            in.setstate(std::ios::failbit);
        }
        return in;
    }
    std::istream& operator>>(std::istream& in, DoubleIO&& dest) {
        std::istream::sentry sentry(in);
        if (!sentry) {
            return in;
        }
        int beforeDot = 0;
        if (!(in >> beforeDot)) {
            in.setstate(std::ios_base::failbit);
            return in;
        }
        in >> DelimiterIO{ '.' };
        int afterDot = 0;
        if (!(in >> afterDot)) {
            in.setstate(std::ios_base::failbit);
            return in;
        }
        char exponentChar = '0';
        in >> exponentChar;
        if (!((exponentChar == 'E') || (exponentChar == 'e'))) {
            in.setstate(std::ios_base::failbit);
            return in;
        }
        int exponent = 0;
        if (!(in >> exponent)) {
            in.setstate(std::ios_base::failbit);
            return in;
        }
        // получение разряда числа после точки
        int n = 0;
        int afterDotCopy = afterDot;
        while (afterDotCopy != 0) {
            afterDotCopy /= 10;
            n++;
        }
        // обработка
        double mantissa = 0;
        if (beforeDot > 0) {
            mantissa = beforeDot + (afterDot / std::pow(10.0, n));
        } else {
            mantissa = -(beforeDot + (afterDot / std::pow(10.0, n)));
        }
        dest.ref = mantissa * std::pow(10.0, exponent);
        return in;
    }
    std::istream& operator>>(std::istream& in, LongIO&& dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        int number = 0;
        if (!(in >> number)) {
            in.setstate(std::ios_base::failbit);
            return in;
        }
        char firstL = '0';
        char secondL = '0';
        in >> firstL >> secondL;
        if (!((firstL == 'l' || firstL == 'L') && (secondL == 'l' || secondL == 'L'))) {
            in.setstate(std::ios_base::failbit);
            return in;
        }
        dest.ref = number;
        return in;
    }
    std::istream& operator>>(std::istream& in, StringKeyIO&& dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        return std::getline(in >> DelimiterIO {'"'}, dest.ref, '"');
    }
    std::istream& operator>>(std::istream& in, KeyIO&& dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        std::string data = "";
        in >> StringKeyIO{ data };
        if (in && (data != dest.exp))
        {
            in.setstate(std::ios::failbit);
        }
        return in;
    }
    std::istream& operator>>(std::istream& in, StringLabelIO&& dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        return std::getline(in, dest.ref, ' ');
    }
    std::istream& operator>>(std::istream& in, LabelIO&& dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        std::string data = "";
        in >> StringLabelIO{ data };
        if (in && (data != dest.exp))
        {
            in.setstate(std::ios::failbit);
        }
        return in;
    }
    std::istream& operator>>(std::istream& in, Data& dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        Data input;
        {
            // starting parenthesis
            if (!(in >> DelimiterIO{ '(' } >> DelimiterIO{ ':' })) {
                in.setstate(std::ios_base::failbit);
                return in;
            }
            bool flagKey1 = false;
            bool flagKey2 = false;
            bool flagKey3 = false;
            // key reading
            for (std::size_t i = 0; i < 3; i++) {
                std::string key = "";
                in >> StringLabelIO{ key };
                if (!flagKey1 && (key == "key1")) {
                    if (!(in >> DoubleIO{ input.key1 })) {
                        break;
                    }
                    flagKey1 = true;
                }
                else if (!flagKey2 && (key == "key2")) {
                    if (!(in >> LongIO{ input.key2 })) {
                        break;
                    }
                    flagKey2 = true;
                }
                else if (!flagKey3 && (key == "key3")) {
                    if (!(in >> StringKeyIO{ input.key3 })) {
                        break;
                    }
                    flagKey3 = true;
                }
                else {
                    in.setstate(std::ios_base::failbit);
                    break;
                }
                if (std::isspace(in.peek())) {
                    in.setstate(std::ios::failbit);
                    break;
                }
                if (!(in >> DelimiterIO{ ':' })) break;
            }
            // ending parenthesis
            if ((in >> DelimiterIO{ ')' }) && flagKey1 && flagKey2 && flagKey3) {
                dest = input;
            }
            else {
                in.setstate(std::ios::failbit);
            }
        }
        return in;
    }
    std::string makeScientific(double key1) {
        if (key1 == 0.0) {
            return "0.0e+0";
        }
        int exponent = 0;
        bool isNegative = false;
        double mantissa = 0;
        if (key1 < 0) {
            isNegative = true;
            mantissa = -key1;
        }
        else {
            isNegative = false;
            mantissa = key1;
        }
        if (mantissa >= 10.0) {
            while (mantissa >= 10.0) {
                mantissa = mantissa / 10.0;
                exponent = exponent + 1;
            }
        }
        else if (mantissa < 1.0) {
            while (mantissa < 1.0) {
                mantissa = mantissa * 10.0;
                exponent = exponent - 1;
            }
        }
        std::stringstream result;
        result << std::fixed << std::setprecision(1) << (isNegative ? -mantissa : mantissa);
        result << "e";
        if (exponent >= 0) {
            result << "+";
        }
        result << exponent;
        return result.str();
    }
    std::ostream& operator<<(std::ostream& out, const Data& src)
    {
        std::ostream::sentry sentry(out);
        if (!sentry)
        {
            return out;
        }
        iofmtguard fmtguard(out);
        out << std::fixed << std::setprecision(1) << std::defaultfloat;
        out << "(:key1 " << makeScientific(src.key1) << ":key2 " << src.key2 << "ll:key3 \"" << src.key3;
        out << "\":)";
        return out;
    }
    iofmtguard::iofmtguard(std::basic_ios< char >& s) :
        s_(s),
        width_(s.width()),
        fill_(s.fill()),
        precision_(s.precision()),
        fmt_(s.flags())
    {}
    iofmtguard::~iofmtguard()
    {
        s_.width(width_);
        s_.fill(fill_);
        s_.precision(precision_);
        s_.flags(fmt_);
    }
    bool comparator(const nspace::Data& a, const nspace::Data& b) {
        if (a.key1 != b.key1) {
            return a.key1 < b.key1;
        }
        else if (a.key2 != b.key2) {
            return a.key2 < b.key2;
        }
        else {
            return a.key3.length() < b.key3.length();
        }
    }
}
