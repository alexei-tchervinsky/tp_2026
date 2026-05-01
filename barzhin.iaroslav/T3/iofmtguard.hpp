#ifndef T3_IOFMTGUARD_HPP
#define T3_IOFMTGUARD_HPP

#include <iomanip>

class iofmtguard {
    std::basic_ios<char>& s_;
    std::streamsize width_;
    char fill_;
    std::streamsize precision_;
    std::basic_ios<char>::fmtflags fmt_;
public:
    iofmtguard(std::basic_ios<char>& s);
    ~iofmtguard();
};

#endif //T3_IOFMTGUARD_HPP
