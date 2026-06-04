#include "DataStruct.hpp"
#include <iomanip>

std::istream &operator>>(std::istream &in, DelimiterIO &&dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  char c = 0;
  in >> c;
  if (c != dest.expected)
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::istream &operator>>(std::istream &in, LabelIO &&dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  for (char expected_char : dest.expected)
  {
    char c = 0;
    in >> c;
    if (c != expected_char)
    {
      in.setstate(std::ios::failbit);
      break;
    }
  }
  return in;
}

std::istream &operator>>(std::istream &in, DblLitIO &&dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }

  double val = 0.0;
  if (in >> val)
  {
    char suffix = 0;
    in >> suffix;
    if (suffix == 'd' || suffix == 'D')
    {
      dest.ref = val;
    }
    else
    {
      in.setstate(std::ios::failbit);
    }
  }
  return in;
}

std::istream &operator>>(std::istream &in, UllHexIO &&dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }

  char zero = 0, x = 0;
  in >> zero >> x;
  if (zero == '0' && (x == 'x' || x == 'X'))
  {
    unsigned long long val = 0;
    if (in >> std::hex >> val)
    {
      dest.ref = val;
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
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }

  in >> DelimiterIO{'"'};
  if (in)
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

  bool has_key1 = false, has_key2 = false, has_key3 = false;

  for (int i = 0; i < 3; ++i)
  {
    std::string key_name;
    char c = 0;
    while (in >> c && c != ' ' && c != ':')
    {
      key_name += c;
    }

    if (key_name == "key1" && !has_key1)
    {
      in >> DblLitIO{dest.key1};
      has_key1 = true;
    }
    else if (key_name == "key2" && !has_key2)
    {
      in >> UllHexIO{dest.key2};
      has_key2 = true;
    }
    else if (key_name == "key3" && !has_key3)
    {
      in >> StringIO{dest.key3};
      has_key3 = true;
    }
    else
    {
      in.setstate(std::ios::failbit);
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
