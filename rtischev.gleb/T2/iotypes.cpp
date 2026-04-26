#include "iotypes.hpp"


// Реализация оператора для DelimetrIO
std::istream& operator>>(std::istream& in, DelimetrIO&& dest)
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

// перегрузка оператора ввода дл¤ структуры UllHexIO
std::istream& operator>>(std::istream& in, UllHexIO&& dest)
{

    std::istream::sentry sentry(in);
    if (!sentry)
    {
        return in;
    }

    in >> std::hex >> dest.ref;
    in >> std::dec;
    return in;
}

// перегрузка оператора ввода дл¤ структуры RationalIO
std::istream& operator>>(std::istream& in, RationalIO&& dest)
{
    std::istream::sentry sentry(in);
    if (!sentry)
    {
        return in;
    }

    long long num = 0 ;
    unsigned long long den = 0;

    in >> DelimetrIO{'('} >> DelimetrIO{':'} >> DelimetrIO{'N'} >> num;
    in >> DelimetrIO{':'} >> DelimetrIO{'D'} >> den >> DelimetrIO{':'} >> DelimetrIO{''};

    if (in)
    {
        if (den != 0) {
            dest.ref = std::make_pair(num, den);
        } else {
            in.setstate(std::ios::failbit);
        }
    }

    return in;
}

// перегрузка оператора ввода дл¤ структуры StringIO
std::istream& operator>>(std::istream& in, StringIO&& dest)
{
    std::istream::sentry sentry(in);
    if (!sentry)
    {
        return in;
    }
    return std::getline(in >> DelimetrIO{ '"' }, dest.ref, '"');
}

// перегрузка оператора ввода дл¤ структуры KeyIO
std::istream& operator>>(std::istream& in, KeyIO&& dest)
{
    std::istream::sentry sentry(in);
    if (!sentry)
    {
        return in;
    }

    while (in && std::isalnum(in.peek()))
    {
        dest.ref.push_back(in.get());
    }

    bool isKeyCorrect = dest.ref == "key1" || dest.ref == "key2" || dest.ref == "key3";
    if (!(in && isKeyCorrect))
    {
        in.setstate(std::ios::failbit);
    }
    return in;
}

