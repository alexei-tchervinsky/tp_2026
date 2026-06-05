#ifndef IOFMTGUARD_HPP
#define IOFMTGUARD_HPP

#include <iomanip>

namespace nspace
{
// scope guard для возврата состояния потока в первоначальное состояние
  class iofmtguard
  {
  public:
    iofmtguard(std::basic_ios< char >& s);
    ~iofmtguard();
  private:
    std::basic_ios< char >& s_;
    std::streamsize width_;
    char fill_;
    std::streamsize precision_;
    std::basic_ios< char >::fmtflags fmt_;
  };
} // namespace

#endif // IOFMTGUARD_HPP
