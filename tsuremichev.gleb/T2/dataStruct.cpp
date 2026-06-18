#include "dataStruct.hpp"
#include "iofmtguard.hpp"
#include <iostream>
#include <iomanip>
#include <cctype>
#include <cmath>
#include <sstream>
#include <algorithm>

namespace nspace
{
  std::istream &operator>>(std::istream &in, DelimetrIO &&dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
      return in;
    char c = '0';
    in >> c;
    if (in && (c != dest.exp))
    {
      in.setstate(std::ios::failbit);
    }
    return in;
  }

  std::istream &operator>>(std::istream &in, DoubleSciIO &&dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
      return in;

    std::string token;
    while (in && (std::isdigit(in.peek()) || in.peek() == '.' ||
                  in.peek() == '-' || in.peek() == '+' ||
                  in.peek() == 'e' || in.peek() == 'E'))
    {
      token.push_back(in.get());
    }

    if (token.empty())
    {
      in.setstate(std::ios::failbit);
      return in;
    }

    if (token.find('e') == std::string::npos &&
        token.find('E') == std::string::npos)
    {
      in.setstate(std::ios::failbit);
      return in;
    }

    std::stringstream ss(token);
    if (!(ss >> dest.ref))
    {
      in.setstate(std::ios::failbit);
    }

    return in;
  }

  std::istream &operator>>(std::istream &in, ComplexLspIO &&dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
      return in;
    double real = 0.0;
    double imag = 0.0;
    in >> DelimetrIO{'#'} >> DelimetrIO{'c'} >> DelimetrIO{'('} >>
        real >> imag >> DelimetrIO{')'};
    if (in)
    {
      dest.ref = {real, imag};
    }
    return in;
  }

  std::istream &operator>>(std::istream &in, StringIO &&dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
      return in;
    return std::getline(in >> DelimetrIO{'"'}, dest.ref, '"');
  }

  std::istream &operator>>(std::istream &in, KeyIO &&dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
      return in;
    dest.ref.clear();
    while (in && std::isalnum(in.peek()))
    {
      dest.ref.push_back(in.get());
    }
    return in;
  }

  std::istream &operator>>(std::istream &in, DataStruct &dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
      return in;

    DataStruct input;
    bool keys_valid[3] = {false, false, false};
    std::string key_current;

    in >> DelimetrIO{'('};
    for (size_t i = 0; i < 3; ++i)
    {
      in >> DelimetrIO{':'} >> KeyIO{key_current};

      if (in && key_current == "key1")
      {
        in >> ComplexLspIO{input.key1};
        if (in)
          keys_valid[0] = true;
      }
      else if (in && key_current == "key2")
      {
        in >> DoubleSciIO{input.key2};
        if (in)
          keys_valid[1] = true;
      }
      else if (in && key_current == "key3")
      {
        in >> StringIO{input.key3};
        if (in)
          keys_valid[2] = true;
      }
      else
      {
        in.setstate(std::ios::failbit);
      }
    }
    in >> DelimetrIO{':'} >> DelimetrIO{')'};

    if (in)
    {
      if (keys_valid[0] && keys_valid[1] && keys_valid[2])
      {
        dest = std::move(input);
      }
      else
      {
        in.setstate(std::ios::failbit);
      }
    }
    return in;
  }

  std::ostream &operator<<(std::ostream &out, const DataStruct &src)
  {
    std::ostream::sentry sentry(out);
    if (!sentry)
    {
      return out;
    }
    iofmtguard guard(out);

    out << "(:key1 #c(" << std::fixed << std::setprecision(1)
        << src.key1.real() << " " << src.key1.imag() << ")";

    std::stringstream ss;
    ss << std::scientific << std::nouppercase
       << std::setprecision(1) << src.key2;
    std::string sci_str = ss.str();

    size_t e_pos = sci_str.find('e');
    if (e_pos != std::string::npos)
    {
      std::string mantissa = sci_str.substr(0, e_pos + 1);
      std::string exponent = sci_str.substr(e_pos + 1);

      if (exponent.length() > 2 && (exponent[1] == '0'))
      {
        exponent.erase(1, 1);
      }
      sci_str = mantissa + exponent;
    }

    out << ":key2 " << sci_str;
    out << ":key3 \"" << src.key3 << "\":)";

    return out;
  }

  bool DataStruct::operator<(const DataStruct &other) const
  {
    double abs1 = std::abs(key1);
    double abs2 = std::abs(other.key1);
    if (abs1 != abs2)
    {
      return abs1 < abs2;
    }
    if (key2 != other.key2)
    {
      return key2 < other.key2;
    }
    return key3.length() < other.key3.length();
  }

}
