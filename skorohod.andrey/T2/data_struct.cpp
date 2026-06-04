#include "data_struct.hpp"
#include "iofmtguard.hpp"
#include <iostream>

namespace asik
{
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

  std::istream& operator>>(std::istream& in, RatLspIO&& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    in >> DelimiterIO{ '(' } >> DelimiterIO{ ':' } >> DelimiterIO{ 'N' }
       >> dest.ref.first >> DelimiterIO{ ':' } >> DelimiterIO{ 'D' }
       >> dest.ref.second >> DelimiterIO{ ':' } >> DelimiterIO{ ')' };
    return in;
  }

  std::istream& operator>>(std::istream& in, StringIO&& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    std::getline(in >> DelimiterIO{ '"' }, dest.ref, '"');
    return in;
  }

  std::istream& operator>>(std::istream& in, CharIO&& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    in >> DelimiterIO{ '\'' } >> dest.ref >> DelimiterIO{ '\'' };
    return in;
  }

  std::istream& operator>>(std::istream& in, DataStruct& dest)
  {
      std::istream::sentry sentry(in);
      if (!sentry)
      {
          return in;
      }
      in >> DelimiterIO{ '(' } >> DelimiterIO{ ':' };
      DataStruct input;
      bool hasKey1 = false, hasKey2 = false, hasKey3 = false;
      while (in && in.peek() != ')')
      {
          if (in.peek() == ')') break;

          std::string key;
          std::getline(in, key, ' ');
          in >> std::ws;

          if (key == "key1")
          {
              in >> RatLspIO{ input.key1 };
              hasKey1 = true;
          }
          else if (key == "key2")
          {
              in >> CharIO{ input.key2 };
              hasKey2 = true;
          }
          else if (key == "key3")
          {
              in >> StringIO{ input.key3 };
              hasKey3 = true;
          }
          else
          {
              in.setstate(std::ios::failbit);
              break;
          }

          in >> DelimiterIO{ ':' };
          if (!in) break;
      }

      in >> DelimiterIO{ ')' };
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

  bool DataStruct::operator<(const DataStruct& other) const
  {
      long double val1 = static_cast<long double>(key1.first) / key1.second;
      long double val2 = static_cast<long double>(other.key1.first) / other.key1.second;
      if (val1 != val2)
      {
          return val1 < val2;
      }
      if (key2 != other.key2)
      {
          return key2 < other.key2;
      }
      return key3.length() < other.key3.length();
  }

  std::ostream& operator<<(std::ostream& out, const DataStruct& src)
  {
    std::ostream::sentry sentry(out);
    if (!sentry)
    {
      return out;
    }
    iofmtguard fmtguard(out);
    out << "(:key1 (:N " << src.key1.first << ":D " << src.key1.second << ":)"
      << ":key2 '" << src.key2 << "'"
      << ":key3 \"" << src.key3 << "\":)";
    return out;
  }
}
