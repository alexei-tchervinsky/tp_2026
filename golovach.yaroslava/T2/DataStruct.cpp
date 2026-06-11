#include "DataStruct.hpp"
#include "iofmtguard.hpp"
#include <iomanip>
#include <cmath>
#include <limits>

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
  in >> dest.ref;
  return in;
}

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

std::istream& operator>>(std::istream& in, StringIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  return std::getline(in >> DelimiterIO{ '"' }, dest.ref, '"');
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
  bool hasKey3 = false;

  in >> DelimiterIO{ '(' } >> DelimiterIO{ ':' };

  for (int i = 0; i < 3 && in; ++i)
  {
    std::string keyName;
    in >> keyName;

    if (!in)
    {
      break;
    }

    if (keyName == "key1")
    {
      in >> DblSciIO{ input.key1 } >> DelimiterIO{ ':' };
      if (in)
      {
        hasKey1 = true;
      }
    }
    else if (keyName == "key2")
    {
      in >> CharLitIO{ input.key2 } >> DelimiterIO{ ':' };
      if (in)
      {
        hasKey2 = true;
      }
    }
    else if (keyName == "key3")
    {
      in >> StringIO{ input.key3 } >> DelimiterIO{ ':' };
      if (in)
      {
        hasKey3 = true;
      }
    }
    else
    {
      in.setstate(std::ios::failbit);
    }
  }

  if (in)
  {
    in >> DelimiterIO{ ')' };
  }

  if (in && hasKey1 && hasKey2 && hasKey3)
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
  out << "(:key1 " << std::scientific << std::setprecision(6) << src.key1;
  out << ":key2 '" << src.key2 << "'";
  out << ":key3 \"" << src.key3 << "\"";
  out << ":)";
  return out;
}

bool DataStruct::operator<(const DataStruct& other) const
{
  if (key1 != other.key1)
  {
    return key1 < other.key1;
  }
  if (key2 != other.key2)
  {
    return key2 < other.key2;
  }
  return key3.size() < other.key3.size();
}

bool DataStructComparator::operator()(const DataStruct& lhs,
                                      const DataStruct& rhs) const
{
  return lhs < rhs;
}

