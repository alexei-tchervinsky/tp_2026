#include "dataStruct.hpp"
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <cmath>
#include "iofmtguard.hpp"

std::istream &operator>>(std::istream &in, DataStruct &dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
    return in;

  DataStruct temp;

  in >> DelimetrIO{'('};

  for (int i = 0; i < 3; ++i)
  {
    std::string key = "";
    in >> DelimetrIO{':'} >> KeyIO{key};

    if (key == "key1")
    {
      in >> ComplexLspIO{temp.key1};
    }
    else if (key == "key2")
    {
      in >> DoubleSciIO{temp.key2};
    }
    else if (key == "key3")
    {
      in >> StringIO{temp.key3};
    }
    else
    {
      in.setstate(std::ios::failbit);
    }
  }

  in >> DelimetrIO{':'} >> DelimetrIO{')'};

  if (in)
  {
    dest = temp;
  }

  return in;
}

std::ostream &operator<<(std::ostream &out, const DataStruct &src)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
    return out;

  iofmtguard guard(out);

  out << "(:key1 #c(" << std::fixed << std::setprecision(1)
      << src.key1.real() << " " << src.key1.imag() << ")";

  out << ":key2 " << std::scientific << std::nouppercase
      << std::setprecision(1) << src.key2;

  out << ":key3 \"" << src.key3 << "\":)";

  return out;
}

bool operator<(const DataStruct &lhs, const DataStruct &rhs)
{
  if (std::abs(lhs.key1) != std::abs(rhs.key1))
  {
    return std::abs(lhs.key1) < std::abs(rhs.key1);
  }
  if (lhs.key2 != rhs.key2)
  {
    return lhs.key2 < rhs.key2;
  }
  return lhs.key3.length() < rhs.key3.length();
}
