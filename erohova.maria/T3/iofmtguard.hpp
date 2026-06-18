#ifndef IOFMTGUARD_HPP
#define IOFMTGUARD_HPP

#include <iostream>

class iofmtguard {
public:
    explicit iofmtguard(std::ostream& s);
    ~iofmtguard();
private:
    std::ostream& stream;
    std::ios_base::fmtflags flags;
    std::streamsize precision;
};

#endif
