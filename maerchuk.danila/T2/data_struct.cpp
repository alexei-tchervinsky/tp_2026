#include "data_struct.hpp"
#include "iofmtguard.hpp"
#include <iomanip>
#include <string>

namespace nspace
{
  // Парсинг разделителя (одиночного символа)
  std::istream& operator>>(std::istream& in, DelimiterIO&& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry) return in;
    char c = '0';
    if (in >> c && (std::tolower(c) != std::tolower(dest.exp)))
    {
      in.setstate(std::ios::failbit);
    }
    return in;
  }

  // Парсинг фиксированной строки (например, "key")
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

  // CHR LIT: 'a'
  std::istream& operator>>(std::istream& in, CharIO&& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry) return in;
    return in >> DelimiterIO{ '\'' } >> dest.ref >> DelimiterIO{ '\'' };
  }

  // DBL SCI: 1.0e+2
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

  // STRING: "data"
  std::istream& operator>>(std::istream& in, StringIO&& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry) return in;
    return std::getline(in >> DelimiterIO{ '"' }, dest.ref, '"');
  }

  // Чтение всей структуры DataStruct
  std::istream& operator>>(std::istream& in, DataStruct& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry) return in;

    DataStruct input;
    bool keys_found[3] = {false, false, false};

    in >> DelimiterIO{ '(' } >> DelimiterIO{ ':' };

    for (int i = 0; i < 3; ++i)
    {
      char key_num = '0';
      // Посимвольно считываем "key" и номер (1, 2 или 3)
      if (!(in >> LabelIO{ "key" } >> key_num)) break;

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
    else
    {
      in.setstate(std::ios::failbit);
    }
    return in;
  }

  // Сравнение для сортировки
  bool DataStruct::operator<(const DataStruct& other) const
  {
    if (key1 != other.key1) return key1 < other.key1;
    if (key2 != other.key2) return key2 < other.key2;
    return key3.length() < other.key3.length();
  }

  // Вывод в поток
  std::ostream& operator<<(std::ostream& out, const DataStruct& src)
  {
    std::ostream::sentry sentry(out);
    if (!sentry) return out;
    iofmtguard fmtguard(out);
    out << "(:key1 '" << src.key1 << "':key2 "
        << std::scientific << std::setprecision(1) << std::nouppercase << src.key2
        << ":key3 \"" << src.key3 << "\":)";
    return out;
  }
}
