#include "DataStruct.h"
#include "iofmtguard.hpp"
#include <limits>
#include <iomanip>

// вспомогательные операторы ввода

// Читает ровно один символ-разделитель (пропускает пробелы через sentry/>>)
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

// Читает беззнаковое целое в hex-формате: 0xFF, 0xABC, 0X1a
// std::hex вместе с >> сам распознаёт префикс 0x/0X
std::istream& operator>>(std::istream& in, UllHexIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  in >> std::hex >> dest.ref >> std::dec;
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
  // Открывающая кавычка, один символ (get не пропускает пробелы), закрывающая кавычка
  in >> DelimiterIO{ '\'' };
  in.get(dest.ref);
  in >> DelimiterIO{ '\'' };
  return in;
}

// Читает строку в двойных кавычках: "Hello world"
std::istream& operator>>(std::istream& in, StringIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  return std::getline(in >> DelimiterIO{ '"' }, dest.ref, '"');
}

// Читает ключевое слово без кавычек и проверяет совпадение с ожидаемым
std::istream& operator>>(std::istream& in, LabelIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  std::string data;
  if ((in >> data) && (data != dest.exp))
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

// оператор ввода для дата структ
// Формат: (:key1 0xFF:key2 'A':key3 "Hello":)
// поля могут идти в любом порядке
//Собирает всё вместе: читает строку, парсит поля, заполняет структуру
// плохие строки пропускаются — цикл продолжается до следующей валидной записи.
std::istream& operator>>(std::istream& in, DataStruct& dest)
{
  // Пробуем читать строки пока не найдём валидную запись или не кончится поток
  while (in.good())
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      break;
    }

    DataStruct input;
    bool hasKey1 = false;
    bool hasKey2 = false;
    bool hasKey3 = false;

    // Сохраняем позицию: если разбор не удастся — пропускаем до конца строки
    std::streampos lineStart = in.tellg();

    {
      using sep = DelimiterIO;
      using hex = UllHexIO;
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
          in >> hex{ input.key1 } >> sep{ ':' };
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
      // Запись успешно прочитана
      dest = std::move(input);
      return in;
    }

    // Запись невалидна — очищаем failbit и пропускаем остаток строки
    in.clear();
    in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }

  // Поток исчерпан — выставляем failbit, чтобы istream_iterator остановился
  in.setstate(std::ios::failbit);
  return in;
}

// оператор вывода
// Формат вывода совпадает с форматом ввода: (:key1 0xFF:key2 'A':key3 "Hello":)
// iofmtguard восстанавливает флаги форматирования потока после вывода
std::ostream& operator<<(std::ostream& out, const DataStruct& src)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  iofmtguard fmtguard(out);
  out << "(:key1 0x" << std::hex << std::uppercase << src.key1;
  out << ":key2 '" << src.key2 << "'";
  out << ":key3 \"" << src.key3 << "\"";
  out << ":)";
  return out;
}

// оператор сравнения
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

// компаратор
bool DataStructComparator::operator()(const DataStruct& lhs,
                                      const DataStruct& rhs) const
{
  return lhs < rhs;
}
