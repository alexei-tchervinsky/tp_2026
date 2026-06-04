#include "dataStruct.hpp"
#include <iomanip>
#include <sstream>
#include <cmath>

std::istream &operator>>(std::istream &in, DelimiterIO &&) { return in; }
std::istream &operator>>(std::istream &in, LabelIO &&) { return in; }

std::istream &operator>>(std::istream &in, DataStruct &dest)
{
  std::string line;
  if (!std::getline(in, line))
    return in;
  if (line.empty())
    return in;

  if (!line.empty() && line.back() == '\r')
  {
    line.pop_back();
  }

  if (line.find('(') == std::string::npos || line.find(')') == std::string::npos)
  {
    in.setstate(std::ios::failbit);
    return in;
  }

  size_t p1 = line.find(":key1");
  size_t p2 = line.find(":key2");
  size_t p3 = line.find(":key3");

  if (p1 == std::string::npos || p2 == std::string::npos || p3 == std::string::npos)
  {
    in.setstate(std::ios::failbit);
    return in;
  }

  DataStruct input;

  size_t c_start = line.find("#c(", p1);
  if (c_start == std::string::npos)
  {
    in.setstate(std::ios::failbit);
    return in;
  }
  size_t c_end = line.find(')', c_start);
  if (c_end == std::string::npos)
  {
    in.setstate(std::ios::failbit);
    return in;
  }
  std::string c_sub = line.substr(c_start + 3, c_end - c_start - 3);
  std::stringstream c_ss(c_sub);
  double re, im;
  if (c_ss >> re >> im)
  {
    input.key1 = {re, im};
  }
  else
  {
    in.setstate(std::ios::failbit);
    return in;
  }

  size_t col_after_k2 = line.find(':', p2 + 5);
  if (col_after_k2 == std::string::npos)
  {
    in.setstate(std::ios::failbit);
    return in;
  }
  std::string k2_sub = line.substr(p2 + 5, col_after_k2 - p2 - 5);

  if (k2_sub.find_first_of("eE") == std::string::npos ||
      k2_sub.find_first_of("dDlLuU'#(") != std::string::npos)
  {
    in.setstate(std::ios::failbit);
    return in;
  }
  std::stringstream k2_ss(k2_sub);
  double val;
  if (k2_ss >> val)
  {
    input.key2 = val;
  }
  else
  {
    in.setstate(std::ios::failbit);
    return in;
  }

  size_t q_start = line.find('"', p3);
  if (q_start == std::string::npos)
  {
    in.setstate(std::ios::failbit);
    return in;
  }
  size_t q_end = line.find('"', q_start + 1);
  if (q_end == std::string::npos)
  {
    in.setstate(std::ios::failbit);
    return in;
  }
  input.key3 = line.substr(q_start + 1, q_end - q_start - 1);

  dest = input;
  return in;
}

std::ostream &operator<<(std::ostream &out, const DataStruct &src)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
    return out;

  out << "(:key1 #c(" << std::fixed << std::setprecision(1) << src.key1.real()
      << " " << src.key1.imag() << ")"
      << ":key2 " << std::scientific << std::setprecision(2) << src.key2
      << ":key3 \"" << src.key3 << "\":)";
  return out;
}
