#include "dataStruct.hpp"
#include <cmath>
#include <iomanip>
#include <sstream>
// #include <cctype>

struct DelimiterIO
{
  char expected;
};
struct LabelIO
{
  std::string expected;
};

// Чтение конкретного символа-разделителя
std::istream &operator>>(std::istream &in, DelimiterIO &&dest)
{
  std::istream::sentry guard(in);
  if (!guard)
    return in;
  char c;
  if (in >> c && c != dest.expected)
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

// Чтение метки ключа (например, ":key1")
std::istream &operator>>(std::istream &in, LabelIO &&dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  std::string actual;
  char c;
  for (size_t i = 0; i < dest.expected.length(); ++i)
  {
    if (in.get(c))
    {
      actual += c;
    }
  }
  if (actual != dest.expected)
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::istream &operator>>(std::istream &in, DataStruct &dest)
{
  std::string line;
  // std::istream::sentry sentry(in);
  if (!std::getline(in, line))
  {
    return in;
  }

  if (line.empty())
  {
    return in;
  }
  std::stringstream ss(line);
  char open1;
  char open2;

  if (!(ss >> open1 >> open2) || open1 != '(' || open2 != ':')
  {
    in.setstate(std::ios::failbit);
    return in;
  }
  DataStruct input;
  bool has_k1 = false;
  bool has_k2 = false;
  bool has_k3 = false;
  // in >> DelimiterIO{'('} >> DelimiterIO{':'};
  for (std::size_t i = 0; i < 3; ++i)
  {
    std::string key;
    char ch;
    // std::getline(in, key, ' '); // Читаем имя ключа до пробела ("key1", "key2" или "key3")
    while (ss.get(ch) && ch != ' ')
    {
      key += ch;
    }
    if (key == "key1")
    {
      // Читаем double в научном формате (например, 5.45e-2)
      ss >> std::ws >> input.key1;
    }
    else if (key == "key2")
    {
      // Читаем комплексное число #c(1.0 -1.0)
      double re, im;
      if (ss >> LabelIO{"#c("} >> std::ws >> re >> std::ws >> im >> DelimiterIO{')'})
      {
        input.key2 = {re, im};
        // input.key2 = {re, im};
        has_k2 = true;
      }
      // in >> LabelIO{"#c("} >> re >> im >> DelimiterIO{')'};
    }
    else if (key == "key3")
    {
      // Читаем строку в кавычках
      if (ss >> DelimiterIO{'"'})
      {
        std::getline(in, input.key3, '"');
        has_k3 = true;
      }
      // in >> DelimiterIO{'"'};
    }
    ss >> std::noskipws >> DelimiterIO{':'};
  }
  if (ss && has_k1 && has_k2 && has_k3)
  {
    dest = input;
  }
  else
  {
    in.setstate(std::ios::failbit);
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

  out << "(:key1 " << std::scientific << src.key1
      << ":key2 #c(" << std::fixed << std::setprecision(1) << src.key2.real() << " " << src.key2.imag() << ")"
      << ":key3 \"" << src.key3 << "\":)";
  return out;
}

bool compareDataStruct(const DataStruct &a, const DataStruct &b)
{
  if (std::abs(a.key1 - b.key1) > 1e-9)
  {
    return a.key1 < b.key1;
  }
  double abs_a = std::abs(a.key2);
  double abs_b = std::abs(b.key2);
  if (std::abs(abs_a - abs_b) > 1e-9)
  {
    return abs_a < abs_b;
  }
  return a.key3.length() < b.key3.length();
}
