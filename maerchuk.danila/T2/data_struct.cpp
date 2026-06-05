#include "data_struct.hpp"
#include "iofmtguard.hpp"
#include <iomanip>
#include <string>
#include <cmath>

namespace nspace
{
  // Парсинг разделителя
  std::istream& operator>>(std::istream& in, DelimiterIO&& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry) return in;
    char c;
    if (in >> c && (std::tolower(c) != std::tolower(dest.exp)))
    {
      in.setstate(std::ios::failbit);
    }
    return in;
  }

  // Парсинг метки (key)
  std::istream& operator>>(std::istream& in, LabelIO&& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry) return in;
    for (size_t i = 0; i < dest.exp.length(); ++i)
    {
      char c;
      if (!(in >> c) || (std::tolower(c) != std::tolower(dest.exp[i])))
      {
        in.setstate(std::ios::failbit);
        break;
      }
    }
    return in;
  }

  // CHR LIT: 'a' [cite: 68, 110]
  std::istream& operator>>(std::istream& in, CharIO&& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry) return in;
    return in >> DelimiterIO{ '\'' } >> dest.ref >> DelimiterIO{ '\'' };
  }

  // DBL SCI: 1.0e+2 [cite: 41, 118]
  std::istream& operator>>(std::istream& in, DoubleSciIO&& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry) return in;
    if (!(in >> dest.ref))
    {
      in.setstate(std::ios::failbit);
    }
    return in;
  }

  // STRING: "data" [cite: 22]
  std::istream& operator>>(std::istream& in, StringIO&& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry) return in;
    return std::getline(in >> DelimiterIO{ '"' }, dest.ref, '"');
  }

  // Чтение всей структуры [cite: 24, 25]
  std::istream& operator>>(std::istream& in, DataStruct& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry) return in;

    DataStruct input;
    bool keys_found[3] = {false, false, false};

    in >> DelimiterIO{ '(' } >> DelimiterIO{ ':' };
    for (int i = 0; i < 3 && in; ++i)
    {
      std::string key_label;
      if (!(in >> LabelIO{ "key" })) break;

      char key_num;
      in >> key_num;

      if (key_num == '1')
      {
        in >> CharIO{ input.key1 };
        keys_found[0] = true;
      }
      else if (key_num == '2')
      {
        in >> DoubleSciIO{ input.key2 };
        keys_found[1] = true;
      }
      else if (key_num == '3')
      {
        in >> StringIO{ input.key3 };
        keys_found[2] = true;
      }
      else
      {
        in.setstate(std::ios::failbit);
      }
      in >> DelimiterIO{ ':' };
    }
    in >> DelimiterIO{ ')' };

    if (in && keys_found[0] && keys_found[1] && keys_found[2])
    {
      dest = std::move(input);
    }
    return in;
  }

  // Компаратор для сортировки [cite: 7, 8, 9]
  bool DataStruct::operator<(const DataStruct& other) const
  {
    if (key1 != other.key1) return key1 < other.key1;
    if (std::abs(key2 - other.key2) > 1e-9) return key2 < other.key2;
    return key3.length() < other.key3.length();
  }

  // Функция для вывода double в формате 1.1e+1
  std::string formatDoubleSci(double val)
  {
    char buf[32];
    std::sprintf(buf, "%.1e", val);
    std::string s(buf);
    // Удаляем лишние нули в экспоненте
    size_t e_pos = s.find('e');
    if (e_pos != std::string::npos)
    {
        std::string res = s.substr(0, e_pos + 2); // "1.1e+"
        std::string exp = s.substr(e_pos + 2);   // "01"
        while (exp.length() > 1 && exp[0] == '0')
        {
            exp.erase(0, 1);
        }
        return res + exp;
    }
    return s;
  }

  // Вывод в поток [cite: 12, 32]
  std::ostream& operator<<(std::ostream& out, const DataStruct& src)
  {
    std::ostream::sentry sentry(out);
    if (!sentry) return out;
    iofmtguard fmtguard(out);
    out << "(:key1 '" << src.key1 << "':key2 "
        << formatDoubleSci(src.key2)
        << ":key3 \"" << src.key3 << "\":)";
    return out;
  }
}
