#include "iofmtguard.hpp"

namespace nspace{
    iofmtguard::iofmtguard(std::ios& s) :
     s_(s),
     width_(s.width()),
     fill_(s.fill()),
     precision_(s.precision()),
     fmt_(s.flags()) {}

    iofmtguard::~iofmtguard(){
        s_.fill(fill_);
        s_.width(width_);
        s_.precision(precision_);
        s_.flags(fmt_);
    }
}
