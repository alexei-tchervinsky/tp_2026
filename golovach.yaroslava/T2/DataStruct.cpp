#include "DataStruct.hpp"
#include "Delimiters.hpp"
#include <iomanip>
#include <cmath>

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

    // Читаем начало структуры
    in >> DelimiterString{"(:"};
    if (!in) return in;

    for (size_t i = 0; i < 3; ++i)
    {
        std::string key_name = "";
        char c = 0;

        // Считываем имя ключа до пробела или двоеточия
        while (in.get(c) && c != ' ' && c != ':')
        {
            key_name += c;
        }

        // Если прочитали лишнее двоеточие, возвращаем его
        if (c == ':')
        {
            in.putback(c);
        }

        if (key_name == "key1")
        {
            if (has_key1) { in.setstate(std::ios_base::failbit); return in; }
            double val = 0.0;
            // Явно используем scientific для DBL SCI формата
            if (in >> std::scientific >> val)
            {
                temp.key1 = val;
                has_key1 = true;
            }
        }
        else if (key_name == "key2")
        {
            if (has_key2) { in.setstate(std::ios_base::failbit); return in; }
            char c1 = 0, c2 = 0, c3 = 0;
            if (in >> c1 >> c2 >> c3 && c1 == '\'' && c3 == '\'')
            {
                temp.key2 = c2;
                has_key2 = true;
            }
            else
            {
                in.setstate(std::ios_base::failbit);
                return in;
            }
        }
        else if (key_name == "key3")
        {
            if (has_key3) { in.setstate(std::ios_base::failbit); return in; }
            char quote = 0;
            if (in >> quote && quote == '"')
            {
                std::string str = "";
                if (std::getline(in, str, '"'))
                {
                    temp.key3 = str;
                    has_key3 = true;
                }
            }
            else
            {
                in.setstate(std::ios_base::failbit);
                return in;
            }
        }
        else
        {
            in.setstate(std::ios_base::failbit);
            return in;
        }

        // Перед чтением следующего ключа проверяем разделитель ':'
        in >> DelimiterChar{':'};
        if (!in) return in;
    }

    // Читаем закрывающую скобку
    in >> DelimiterChar{')'};

    if (in && has_key1 && has_key2 && has_key3)
    {
        dest = temp;
    }
    else
    {
        in.setstate(std::ios_base::failbit);
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

    out << "(:key1 ";
    out << std::scientific << std::setprecision(1) << src.key1;
    out << ":key2 '" << src.key2 << "'";
    out << ":key3 \"" << src.key3 << "\":)";
    return out;
}
