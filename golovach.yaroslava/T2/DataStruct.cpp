#include "DataStruct.hpp"
#include <iomanip>
#include <sstream>
#include <cmath>

// Читает ровно один конкретный символ
std::istream& operator>>(std::istream& in, DelimiterIO&& dest)
{
    std::istream::sentry sentry(in); // Проверяет состояние потока
    if (!sentry)
    {
        return in;
    }
    char c = 0;
    in >> c;
    if (in && c != dest.exp)
    {
        in.setstate(std::ios::failbit); // Ломает поток, если символ не совпал с ожидаемым
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

    in >> std::ws; // пропускаем пробелы после ключа
#if 1
    return in >> std::scientific >> dest.ref;
#else
    std::string token;
    char c = 0;
    while (in.get(c) && c != ':') // Считываем все символы числа, пока не упремся в ':'
    {
        token += c;
    }
    if (in && c == ':')
    {
        in.putback(c); // возвращаем ':' обратно в поток
    }

    if (token.empty())
    {
        in.setstate(std::ios::failbit);
        return in;
    }

    // Проверка на отсутствие суффикса d/D
    char last = token.back();
    if (last == 'd' || last == 'D')
    {
        in.setstate(std::ios::failbit);
        return in;
    }

    // Проверка наличия e/E
    size_t epos = token.find_first_of("eE");
    if (epos == std::string::npos)
    {
        in.setstate(std::ios::failbit);
        return in;
    }

    // Проверка точки в мантиссе
    std::string mantissa = token.substr(0, epos);
    size_t dotpos = mantissa.find('.');
    if (dotpos == std::string::npos)
    {
        in.setstate(std::ios::failbit);
        return in;
    }

    //До и после точки должна быть хотя бы одна цифра
    size_t start = (!mantissa.empty() && mantissa[0] == '-') ? 1 : 0;
    if (dotpos == start || dotpos == mantissa.size() - 1)
    {
        in.setstate(std::ios::failbit);
        return in;
    }

    // Если все проверки пройдены, парсим строку в double через строковый поток
    std::istringstream ss(token);
    ss >> dest.ref;
    if (ss.fail())
    {
        in.setstate(std::ios::failbit);
    }
    return in;
#endif    
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

    std::string line;
    if (!std::getline(in, line))
    {
        return in;
    }

    std::istringstream ss(line);
    DataStruct temp{0.0, '\0', ""};
    bool has_key1 = false;
    bool has_key2 = false;
    bool has_key3 = false;

    using sep = DelimiterIO;
    using dbl = DoubleSciIO;
    using chr = CharLitIO;
    using str = StringIO;

    ss >> sep{ '(' };
    if (!ss)
    {
        in.setstate(std::ios::failbit);
        return in;
    }

    for (int i = 0; i < 3 && ss; ++i)
    {
        std::string key_name;
        ss >> sep{ ':' } >> key_name;
        if (!ss)
        {
            break;
        }

        if (key_name == "key1")
        {
            ss >> dbl{ temp.key1 };
            if (ss)
            {
                has_key1 = true;
            }
        }
        else if (key_name == "key2")
        {
            ss >> chr{ temp.key2 };
            if (ss)
            {
                has_key2 = true;
            }
        }
        else if (key_name == "key3")
        {
            ss >> str{ temp.key3 };
            if (ss)
            {
                has_key3 = true;
            }
        }
        else
        {
            ss.setstate(std::ios::failbit);
        }
    }

    // После чтения всех трёх полей
    if (ss)
    {
        ss >> sep{ ':' } >> sep{ ')' };
    }

    if (ss && has_key1 && has_key2 && has_key3)
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
