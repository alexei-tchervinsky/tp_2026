#ifndef IOFMTGUARD_HPP
#define IOFMTGUARD_HPP

#include <ios>

// Scope guard: сохраняет флаги форматирования потока
// и восстанавливает их в деструкторе
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

#endif
