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
    return in >> std::scientific >> dest.ref;
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
    in >> DelimiterIO{ '"' }; // Ожидаем открывающую кавычку
    if (!in)
    {
        return in;
    }
    return std::getline(in, dest.ref, '"');
}

//главный оператор ввода
std::istream& operator>>(std::istream& in, DataStruct& dest)
{
    std::istream::sentry guard(in);
    if (!guard)
    {
        return in;
    }

#if 1
    DataStruct temp{0.0, '\0', ""};
    bool has_key1 = false;
    bool has_key2 = false;
    bool has_key3 = false;

    using sep = DelimiterIO;
    using dbl = DoubleSciIO;
    using chr = CharLitIO;
    using str = StringIO;

    in >> sep{ '(' };
    if (!in)
    {
        in.setstate(std::ios::failbit);
        return in;
    }

    for (int i = 0; i < 3 && in; ++i)
    {
        std::string key_name;
        in >> sep{ ':' } >> key_name;
        if (!in)
        {
            break;
        }

        if (key_name == "key1")
        {
            in >> dbl{ temp.key1 };
            if (in)
            {
                has_key1 = true;
            }
        }
        else if (key_name == "key2")
        {
            in >> chr{ temp.key2 };
            if (in)
            {
                has_key2 = true;
            }
        }
        else if (key_name == "key3")
        {
            in >> str{ temp.key3 };
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

    // После чтения всех трёх полей (если всё успешно)
    if (in)
    {
        in >> sep{ ':' } >> sep{ ')' };
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
#else
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

    // После чтения всех трёх полей (если всё успешно)
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
#endif
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
    size_t epos = s.find('e'); //убираем лишние ведущие нули
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
    //По возрастанию key1
    if (lhs.key1 != rhs.key1)
    {
        return lhs.key1 < rhs.key1;
    }
    //По возрастанию key2 (если key1 равны)
    if (lhs.key2 != rhs.key2)
    {
        return lhs.key2 < rhs.key2;
    }
    //По возрастанию ДЛИНЫ строки key3
    return lhs.key3.length() < rhs.key3.length();
}
