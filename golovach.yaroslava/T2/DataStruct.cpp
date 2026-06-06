#include "DataStruct.h"
#include "iofmtguard.hpp"
#include <limits>
#include <iomanip>

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
  in >> std::scientific >> dest.ref;
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

  {
    using sep = DelimiterIO;
    using dbl = DblSciIO;
    using chr = CharLitIO;
    using str = StringIO;

    in >> sep{ '(' } >> sep{ ':' };

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
        in >> dbl{ input.key1 } >> sep{ ':' };
        if (in)
        {
          hasKey1 = true;
        }
      }
      else if (keyName == "key2")
      {
        in >> chr{ input.key2 } >> sep{ ':' };
        if (in)
        {
          hasKey2 = true;
        }
      }
      else if (keyName == "key3")
      {
        in >> str{ input.key3 } >> sep{ ':' };
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
      in >> sep{ ')' };
    }
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

  out << "(:key1 " << std::scientific << src.key1;
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
}#include "DataStruct.h"
#include "iofmtguard.hpp"
#include <limits>
#include <iomanip>

// Читает ровно один символ-разделитель
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

// Читает double в научном формате (например, 1.23e+04)
std::istream& operator>>(std::istream& in, DblSciIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  in >> std::scientific >> dest.ref;
  return in;
}

// Читает символьный литерал вида 'A'
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

// Оператор ввода для DataStruct (теперь строго для 2 ключей)
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

  {
    using sep = DelimiterIO;
    using dbl = DblSciIO;
    using chr = CharLitIO;

    in >> sep{ '(' } >> sep{ ':' };

    // Цикл на 2 итерации, так как ключа всего два
    for (int i = 0; i < 2 && in; ++i)
    {
      std::string keyName;
      in >> keyName;

      if (!in)
      {
        break;
      }

      if (keyName == "key1")
      {
        in >> dbl{ input.key1 } >> sep{ ':' };
        if (in)
        {
          hasKey1 = true;
        }
      }
      else if (keyName == "key2")
      {
        in >> chr{ input.key2 } >> sep{ ':' };
        if (in)
        {
          hasKey2 = true;
        }
      }
      else
      {
        in.setstate(std::ios::failbit);
      }
    }

    if (in)
    {
      in >> sep{ ')' };
    }
  }

  // Проверяем, что успешно считались оба ключа
  if (in && hasKey1 && hasKey2)
  {
    dest = std::move(input);
  }
  else
  {
    in.setstate(std::ios::failbit);
  }

  return in;
}

// Оператор вывода
std::ostream& operator<<(std::ostream& out, const DataStruct& src)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  iofmtguard fmtguard(out);

  out << "(:key1 " << std::scientific << src.key1;
  out << ":key2 '" << src.key2 << "'";
  out << ":)";
  return out;
}

// Оператор сравнения (сравниваем сначала key1, затем key2)
bool DataStruct::operator<(const DataStruct& other) const
{
  if (key1 != other.key1)
  {
    return key1 < other.key1;
  }
  return key2 < other.key2;
}

// Компаратор
bool DataStructComparator::operator()(const DataStruct& lhs,
                                      const DataStruct& rhs) const
{
  return lhs < rhs;
}#include "DataStruct.h"
#include "iofmtguard.hpp"
#include <limits>
#include <iomanip>

// Читает ровно один символ-разделитель
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
  in >> std::scientific >> dest.ref;
  return in;
}

// Читает символьный литерал вида 'A'
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

  {
    using sep = DelimiterIO;
    using dbl = DblSciIO;
    using chr = CharLitIO;

    in >> sep{ '(' } >> sep{ ':' };


    for (int i = 0; i < 2 && in; ++i)
    {
      std::string keyName;
      in >> keyName;

      if (!in)
      {
        break;
      }

      if (keyName == "key1")
      {
        in >> dbl{ input.key1 } >> sep{ ':' };
        if (in)
        {
          hasKey1 = true;
        }
      }
      else if (keyName == "key2")
      {
        in >> chr{ input.key2 } >> sep{ ':' };
        if (in)
        {
          hasKey2 = true;
        }
      }
      else
      {
        in.setstate(std::ios::failbit);
      }
    }

    if (in)
    {
      in >> sep{ ')' };
    }
  }


  if (in && hasKey1 && hasKey2)
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
  
  out << "(:key1 " << std::scientific << src.key1;
  out << ":key2 '" << src.key2 << "'";
  out << ":)";
  return out;
}


bool DataStruct::operator<(const DataStruct& other) const
{
  if (key1 != other.key1)
  {
    return key1 < other.key1;
  }
  return key2 < other.key2;
}

// Компаратор
bool DataStructComparator::operator()(const DataStruct& lhs,
                                      const DataStruct& rhs) const
{
  return lhs < rhs;
}

