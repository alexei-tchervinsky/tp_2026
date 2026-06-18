#include "DataStruct.hpp"
#include <iomanip>
#include <sstream>

bool compareDataStruct(const DataStruct &a, const DataStruct &b)
{
  if (a.key1 != b.key1)
  {
    return a.key1 < b.key1;
  }
  if (a.key2 != b.key2)
  {
    return a.key2 < b.key2;
  }
  return a.key3.length() < b.key3.length();
}

std::istream &operator>>(std::istream &in, DelimiterIO &&dest)
{
  std::istream::sentry sentry(in, true);
  if (!sentry)
  {
    return in;
  }
  char c = 0;
  if (in.get(c) && c != dest.expected)
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::istream &operator>>(std::istream &in, DblLitIO &&dest)
{
  std::istream::sentry sentry(in, true);
  if (!sentry)
  {
    return in;
  }
  std::string num_str = "";
  char c = 0;
  bool has_dot = false;
  while (in.get(c))
  {
    if (c == 'd' || c == 'D')
    {
      break;
    }
    if (c == '.')
    {
      has_dot = true;
    }
    num_str += c;
  }
  if (!has_dot || num_str.empty())
  {
    in.setstate(std::ios::failbit);
    return in;
  }
  std::stringstream ss(num_str);
  if (!(ss >> dest.ref))
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::istream &operator>>(std::istream &in, UllHexIO &&dest)
{
  std::istream::sentry sentry(in, true);
  if (!sentry)
  {
    return in;
  }
  char zero = 0, x = 0;
  if (in.get(zero) && zero == '0' && in.get(x) && (x == 'x' || x == 'X'))
  {
    std::string hex_str = "";
    char c = 0;
    while (in.peek() != EOF && in.peek() != ':')
    {
      in.get(c);
      hex_str += c;
    }
    if (hex_str.empty())
    {
      in.setstate(std::ios::failbit);
      return in;
    }
    try
    {
      dest.ref = std::stoull(hex_str, nullptr, 16);
    }
    catch (...)
    {
      in.setstate(std::ios::failbit);
    }
  }
  else
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::istream &operator>>(std::istream &in, StringIO &&dest)
{
  std::istream::sentry sentry(in, true);
  if (!sentry)
  {
    return in;
  }
  if (in >> DelimiterIO{'"'})
  {
    std::getline(in, dest.ref, '"');
  }
  return in;
}

std::istream &operator>>(std::istream &in, DataStruct &dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  std::ios_base::fmtflags flags = in.flags();
  if (!(in >> DelimiterIO{'('} >> DelimiterIO{':'}))
  {
    in.flags(flags);
    return in;
  }
  bool has_k1 = false, has_k2 = false, has_k3 = false;
  for (int i = 0; i < 3; ++i)
  {
    std::string key_name = "";
    char ch = 0;
    while (in.get(ch) && ch != ' ')
    {
      key_name += ch;
    }
    if (key_name == "key1" && !has_k1)
    {
      if (in >> DblLitIO{dest.key1})
      {
        has_k1 = true;
      }
    }
    else if (key_name == "key2" && !has_k2)
    {
      if (in >> UllHexIO{dest.key2})
      {
        has_k2 = true;
      }
    }
    else if (key_name == "key3" && !has_k3)
    {
      if (in >> StringIO{dest.key3})
      {
        has_k3 = true;
      }
    }
    else
    {
      in.setstate(std::ios::failbit);
    }
    if (in.fail())
    {
      break;
    }
    if (i < 2)
    {
      if (!(in >> DelimiterIO{':'}))
      {
        in.setstate(std::ios::failbit);
      }
    }
  }
  if (!(in >> DelimiterIO{':'} >> DelimiterIO{')'}))
  {
    in.setstate(std::ios::failbit);
  }
  in.flags(flags);
  return in;
}

std::ostream &operator<<(std::ostream &out, const DataStruct &src)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  std::ios_base::fmtflags flags = out.flags();
  out << "(:key1 " << std::fixed << std::setprecision(1) << src.key1 << "d"
      << ":key2 0x" << std::hex << std::uppercase << src.key2
      << ":key3 \"" << src.key3 << "\":)";
  out.flags(flags);
  return out;
}
