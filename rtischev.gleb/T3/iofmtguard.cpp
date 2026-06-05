#include "iofmtguard.hpp"

iofmtguard::iofmtguard(std::ios &s) : stream_(s),
                                      flags_(s.flags()),
                                      precision_(s.precision()),
                                      fill_(s.fill())
{
}

iofmtguard::~iofmtguard()
{
    stream_.flags(flags_);
    stream_.precision(precision_);
    stream_.fill(fill_);
}
