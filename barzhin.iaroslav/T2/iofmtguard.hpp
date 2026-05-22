//
// Created by xmdnusr on 29.04.2026.
//

#ifndef TP_2026_IOFMTGUARD_HPP
#define TP_2026_IOFMTGUARD_HPP

#include <iomanip>

namespace ds {
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
}

#endif //TP_2026_IOFMTGUARD_HPP
