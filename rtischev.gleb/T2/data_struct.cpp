#include "data_struct.hpp"
#include <sstream>
#include <iomanip>
#include <algorithm>
#include "iofmtguard.hpp"


std::istream& operator>>(std::istream& in, DataStruct& dest)
{
    std::istream::sentry sentry(in);
    if (!sentry) return in;

    DataStruct temp;

    in >> DelimetrIO{'('};

    for (int i = 0; i < 3; ++i) {
        std::string key = "";
        in >> DelimetrIO{':'} >> KeyIO{key};

        if (key == "key1") {
            in >> UllHexIO{temp.key1};
        } else if (key == "key2") {
            in >> RationalIO{temp.key2};
        } else if (key == "key3") {
            in >> StringIO{temp.key3};
        } else {
            in.setstate(std::ios::failbit);
        }
    }

    in >> DelimetrIO{':'} >> DelimetrIO{')'};

    if (in) {
        dest = temp;
    }

    return in;
}

std::ostream& operator<<(std::ostream& out, const DataStruct& src)
{
    std::ostream::sentry sentry(out);
    if (!sentry)
    {
        return out;
    }
    iofmtguard guard(out);

    out << "(:key1 0x" << std::hex << std::uppercase << src.key1;
    out << std::dec << ":key2 (:N " << src.key2.first << ":D " << src.key2.second << ":)";
    out << ":key3 \"" << src.key3 << "\":)";

    return out;
}
