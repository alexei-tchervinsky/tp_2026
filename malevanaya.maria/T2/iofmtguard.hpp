#ifndef IOFMTGUARD_HPP
#define IOFMTGUARD_HPP

#include <ios>

class iofmtguard {
public:
    explicit iofmtguard(std::basic_ios<char>& s);
    ~iofmtguard();
private:
    std::basic_ios<char>& s_;
    char fill_;
    std::streamsize precision_;
    std::basic_ios<char>::fmtflags fmt_;
};

#endif
