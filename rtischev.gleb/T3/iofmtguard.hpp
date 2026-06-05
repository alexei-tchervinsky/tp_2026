#ifndef IOFMTGUARD_HPP
#define IOFMTGUARD_HPP

#include <ios>

class iofmtguard
{
public:
    explicit iofmtguard(std::ios &s);
    ~iofmtguard();

private:
    std::ios &stream_;
    std::ios_base::fmtflags flags_;
    std::streamsize precision_;
    char fill_;
};

#endif
