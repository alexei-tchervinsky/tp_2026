#ifndef IOFMTGUARD_HPP
#define IOFMTGUARD_HPP
#include <iomanip>

namespace nspace{
    class iofmtguard{
        public:
        iofmtguard(std::ios& s);
        ~iofmtguard();
        private:
        std::ios& s_;
        char fill_;
        std::streamsize width_;
        std::streamsize precision_;
        std::ios::fmtflags fmt_;
    };
}
#endif //IOFMTGUARD_HPP
