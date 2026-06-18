#ifndef IOFMTGUARD_HPP
#define IOFMTGUARD_HPP

#include <iostream>

class iofmtguard
{
public:
    explicit iofmtguard(std::ostream &out);
    ~iofmtguard();

private:
    std::ostream &s_;
    std::ios::fmtflags f_;
    std::streamsize p_;
};

#endif
