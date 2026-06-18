#include "iofmtguard.hpp"

iofmtguard::iofmtguard(std::ostream& s) : stream(s), flags(s.flags()), precision(s.precision()) {}

iofmtguard::~iofmtguard() {
    stream.flags(flags);
    stream.precision(precision);
}
