#ifndef IOFORMAT_H
#define IOFORMAT_H

#include <string>
#include <iostream>

struct DelimeterIO
{
  char exp;
};

struct DblLitIO
{
  double& ref;
};

struct SllLitIO
{
  long long& ref;
};

struct StringIO
{
  std::string& ref;
};

std::istream& operator>>(std::istream& in, DelimeterIO&& dest);
std::istream& operator>>(std::istream& in, DblLitIO&& dest);
std::istream& operator>>(std::istream& in, SllLitIO&& dest);
std::istream& operator>>(std::istream& in, StringIO&& dest);

class iofguard
{
public:
  iofguard(std::basic_ios<char>& s);
  ~iofguard();
private:
  std::basic_ios<char>& s_;
  char fill_;
  std::streamsize precision_;
  std::basic_ios<char>::fmtflags fmt_;
};

#endif
