#ifndef DELIMITERS_HPP
#define DELIMITERS_HPP

#include <string>
#include <iostream>

struct DelimiterChar
{
    char expected;
};

struct DelimiterString
{
    std::string expected;
};

std::istream& operator>>(std::istream& in, DelimiterChar&& exp);
std::istream& operator>>(std::istream& in, DelimiterString&& exp);

#endif // DELIMITERS_HPP

