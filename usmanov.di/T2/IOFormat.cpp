#include "IOFormat.h"

std::istream& operator>>(std::istream& in, DelimeterIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }

  char c = '\0';
  in >> c;
  if (in && c != dest.exp)
  {
    in.setstate(std::ios::failbit);
    return in;
  }

  if (in.peek() == ' ')
  {
    in.setstate(std::ios::failbit);
  }

  return in;
}

std::istream& operator>>(std::istream& in, DblLitIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  double value = 0.0;
  in >> value;

  char suffix = '\0';
  in.get(suffix);

  if (in && ((suffix != 'D') && (suffix != 'd')))
  {
    in.setstate(std::ios::failbit);
    return in;
  }

  if (in.peek() == ' ')
  {
    in.setstate(std::ios::failbit);
  }

  dest.ref = value;
  return in;
}

std::istream& operator>>(std::istream& in, SllLitIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }

  long long value = 0;
  if (!(in >> value))
  {
    in.setstate(std::ios::failbit);
    return in;
  }

  if (in.peek() == 'L' || in.peek() == 'l')
  {
    char first, second;
    in.get(first);
    in.get(second);
    if (first != second)
    {
      in.setstate(std::ios::failbit);
      return in;
    }
  }
  if (in.peek() == ' ')
  {
    in.setstate(std::ios::failbit);
  }

  dest.ref = value;
  return in;
}

std::istream& operator>>(std::istream& in, StringIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!in)
  {
    return in;
  }

  in >> DelimeterIO{ '"' };
  if (!in)
  {
    return in;
  }
  std::getline(in, dest.ref, '"');

  if (in.peek() == ' ')
  {
    in.setstate(std::ios::failbit);
  }

  return in;
}

iofguard::iofguard(std::basic_ios<char>& s) :
  s_(s),
  fill_(s.fill()),
  precision_(s.precision()),
  fmt_(s.flags())
{
}

iofguard::~iofguard()
{
  s_.fill(fill_);
  s_.precision(precision_);
  s_.flags(fmt_);
}
