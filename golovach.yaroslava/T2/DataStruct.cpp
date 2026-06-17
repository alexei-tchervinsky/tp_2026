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

    in >> DelimiterString{"(:"};

    for (size_t i = 0; i < 3; ++i)
    {
        in >> DelimiterChar{':'};
        std::string key_name = "";
        std::getline(in, key_name, ' ');

        if (key_name == "key1")
        {
            if (has_key1) { in.setstate(std::ios_base::failbit); return in; }
            double val = 0.0;
            if (in >> val)
            {
                temp.key1 = val;
                has_key1 = true;
            }
        }
        else if (key_name == "key2")
        {
            if (has_key2) { in.setstate(std::ios_base::failbit); return in; }
            char c = 0;
            in >> DelimiterChar{'\''} >> c >> DelimiterChar{'\''};
            if (in)
            {
                temp.key2 = c;
                has_key2 = true;
            }
        }
        else if (key_name == "key3")
        {
            if (has_key3) { in.setstate(std::ios_base::failbit); return in; }
            in >> DelimiterChar{'"'};
            std::string str = "";
            std::getline(in, str, '"');
            if (in)
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

    in >> DelimiterString{":)"};

    if (in && has_key1 && has_key2 && has_key3)
    {
        dest = temp;
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


