#ifndef IOFMTGUARD_HPP
#define IOFMTGUARD_HPP

#include <iostream>

// Класс-хранитель состояния потока ввода/вывода (RAII)
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
