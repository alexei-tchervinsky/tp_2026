#include "DataStruct.h"
#include "iofmtguard.hpp"
#include <limits>
#include <iomanip>

// Читает ровно один символ-разделитель
std::istream& operator>>(std::istream& in, DelimiterIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  char c = '0';
  in >> c;
  if (in && (c != dest.exp))
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}


std::istream& operator>>(std::istream& in, DblSciIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  in >> std::scientific >> dest.ref;
  return in;
}

// Читает символьный литерал вида 'A'
std::istream& operator>>(std::istream& in, CharLitIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  in >> DelimiterIO{ '\'' };
  in.get(dest.ref);
  in >> DelimiterIO{ '\'' };
  return in;
}


std::istream& operator>>(std::istream& in, DataStruct& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }

  DataStruct input;
  bool hasKey1 = false;
  bool hasKey2 = false;

  {
    using sep = DelimiterIO;
    using dbl = DblSciIO;
    using chr = CharLitIO;

    in >> sep{ '(' } >> sep{ ':' };


    for (int i = 0; i < 2 && in; ++i)
    {
      std::string keyName;
      in >> keyName;

      if (!in)
      {
        break;
      }

      if (keyName == "key1")
      {
        in >> dbl{ input.key1 } >> sep{ ':' };
        if (in)
        {
          hasKey1 = true;
        }
      }
      else if (keyName == "key2")
      {
        in >> chr{ input.key2 } >> sep{ ':' };
        if (in)
        {
          hasKey2 = true;
        }
      }
      else
      {
        in.setstate(std::ios::failbit);
      }
    }

    if (in)
    {
      in >> sep{ ')' };
    }
  }


  if (in && hasKey1 && hasKey2)
  {
    dest = std::move(input);
  }
  else
  {
    in.setstate(std::ios::failbit);
  }

  return in;
}


std::ostream& operator<<(std::ostream& out, const DataStruct& src)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  iofmtguard fmtguard(out);
  
  out << "(:key1 " << std::scientific << src.key1;
  out << ":key2 '" << src.key2 << "'";
  out << ":)";
  return out;
}


bool DataStruct::operator<(const DataStruct& other) const
{
  if (key1 != other.key1)
  {
    return key1 < other.key1;
  }
  return key2 < other.key2;
}

// Компаратор
bool DataStructComparator::operator()(const DataStruct& lhs,
                                      const DataStruct& rhs) const
{
  return lhs < rhs;
}
