#include "DataStruct.hpp"
#include <iomanip>
#include <sstream>
#include <cmath>

// Читает ровно один конкретный символ (пропускает пробелы через sentry)
std::istream& operator>>(std::istream& in, DelimiterIO&& dest)
{
    std::istream::sentry sentry(in);
    if (!sentry)
    {
        return in;
    }
    char c = 0;
    in >> c;
    if (in && c != dest.exp)
    {
        in.setstate(std::ios::failbit);
    }
    return in;
}

// Читает double в научном формате: 1.0e-1, 5.0E+2
std::istream& operator>>(std::istream& in, DoubleSciIO&& dest)
{
    std::istream::sentry sentry(in);
    if (!sentry)
    {
        return in;
    }

    // Пропускаем ведущие пробелы перед считыванием токена числа
    char c = 0;
    while (in.get(c) && c == ' ') {}
    if (!in) return in;

    std::string token;
    token += c;

    while (in.get(c) && c != ':' && c != ' ')
    {
        token += c;
    }
    if (in && c == ':')
    {
        in.putback(c);
    }
    if (token.empty())
    {
        in.setstate(std::ios::failbit);
        return in;
    }
    char last = token.back();
    if (last == 'd' || last == 'D')
    {
        in.setstate(std::ios::failbit);
        return in;
    }
    size_t epos = token.find_first_of("eE");
    if (epos == std::string::npos)
    {
        in.setstate(std::ios::failbit);
        return in;
    }
    std::string mantissa = token.substr(0, epos);
    size_t dotpos = mantissa.find('.');
    if (dotpos == std::string::npos)
    {
        in.setstate(std::ios::failbit);
        return in;
    }
    size_t start = (!mantissa.empty() && mantissa[0] == '-') ? 1 : 0;
    if (dotpos == start || dotpos == mantissa.size() - 1)
    {
        in.setstate(std::ios::failbit);
        return in;
    }
    std::istringstream ss(token);
    ss >> dest.ref;
    if (ss.fail())
    {
        in.setstate(std::ios::failbit);
    }
    return in;
}

// Читает символьный литерал вида 'A'
std::istream& operator>>(std::istream& in, CharLitIO&& dest)
{
    std::istream::sentry sentry(in);
    if (!sentry)
    {
        return in;
    }
    in >> DelimiterIO{ '\'' };
    in.get(dest.ref);
    in >> DelimiterIO{ '\'' };
    return in;
}

// Читает строку в двойных кавычках вида "Hello world"
std::istream& operator>>(std::istream& in, StringIO&& dest)
{
    std::istream::sentry sentry(in);
    if (!sentry)
    {
        return in;
    }
    in >> DelimiterIO{ '"' };
    if (!in)
    {
        return in;
    }
    return std::getline(in, dest.ref, '"');
}


std::istream& operator>>(std::istream& in, DataStruct& dest)
{
    std::istream::sentry guard(in);
    if (!guard)
    {
        return in;
    }

    DataStruct temp{0.0, '\0', ""};
    bool has_key1 = false;
    bool has_key2 = false;
    bool has_key3 = false;

    using sep = DelimiterIO;
    using dbl = DoubleSciIO;
    using chr = CharLitIO;
    using str = StringIO;

    // Читает открывающую скобку напрямую из основного потока
    in >> sep{ '(' };
    if (!in)
    {
        return in;
    }

    for (int i = 0; i < 3 && in; ++i)
    {
        in >> sep{ ':' };
        if (!in)
        {
            break;
        }


        std::string key_name;
        char c = 0;
        while (in.get(c) && c != ' ' && c != ':')
        {
            key_name += c;
        }

        if (c == ':')
        {
            in.putback(c);
        }

        if (key_name == "key1")
        {
            in >> dbl{ temp.key1 } >> sep{ ':' };
            if (in)
            {
                has_key1 = true;
            }
        }
        else if (key_name == "key2")
        {
            in >> chr{ temp.key2 } >> sep{ ':' };
            if (in)
            {
                has_key2 = true;
            }
        }
        else if (key_name == "key3")
        {
            in >> str{ temp.key3 } >> sep{ ':' };
            if (in)
            {
                has_key3 = true;
            }
        }
        else
        {
            in.setstate(std::ios::failbit);
        }
    }

    if (in)
    {
        in >> sep{ ')' };
    }

    if (in && has_key1 && has_key2 && has_key3)
    {
        dest = temp;
    }
    else
    {
        in.setstate(std::ios::failbit);
    }

    return in;
}

std::ostream& operator<<(std::ostream& out, const DataStruct& src)
{
    std::ostream::sentry guard(out);
    if (!guard)
    {
        return out;
    }

    std::ostringstream ss;
    ss << std::scientific << std::setprecision(1) << src.key1;
    std::string s = ss.str();
    for (char& ch : s)
    {
        if (ch == 'E')
        {
            ch = 'e';
        }
    }
    size_t epos = s.find('e');
    if (epos != std::string::npos && epos + 2 < s.size())
    {
        std::string exp_part = s.substr(epos + 2);
        size_t nz = exp_part.find_first_not_of('0');
        if (nz == std::string::npos)
        {
            exp_part = "0";
        }
        else
        {
            exp_part = exp_part.substr(nz);
        }
        s = s.substr(0, epos + 2) + exp_part;
    }

    out << "(:key1 " << s;
    out << ":key2 '" << src.key2 << "'";
    out << ":key3 \"" << src.key3 << "\":)";
    return out;
}

bool compareDataStruct(const DataStruct& lhs, const DataStruct& rhs)
{
    if (lhs.key1 != rhs.key1)
    {
        return lhs.key1 < rhs.key1;
    }
    if (lhs.key2 != rhs.key2)
    {
        return lhs.key2 < rhs.key2;
    }
    return lhs.key3.length() < rhs.key3.length();
}
