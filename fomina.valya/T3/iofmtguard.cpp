#include "iofmtguard.hpp"

iofmtguard::iofmtguard(std::ostream &out) : s_(out), f_(out.flags()), p_(out.precision()) {}

iofmtguard::~iofmtguard()
{
    s_.flags(f_);
    s_.precision(p_);
}
