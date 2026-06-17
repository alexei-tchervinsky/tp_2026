#include "Delimiters.hpp"

std::istream& operator>>(std::istream& in, DelimiterChar&& exp)
{
    std::istream::sentry guard(in);
    if (!guard)
    {
        return in;
    }
    char c = 0;
    in >> c;
    if (c != exp.expected)
    {
        in.setstate(std::ios_base::failbit);
    }
    return in;
}

std::istream& operator>>(std::istream& in, DelimiterString&& exp)
{
    std::istream::sentry guard(in);
    if (!guard)
    {
        return in;
    }
    for (char expected_char : exp.expected)
    {
        char c = 0;
        in >> c;
        if (c != expected_char)
        {
            in.setstate(std::ios_base::failbit);
            break;
        }
    }
    return in;
}

