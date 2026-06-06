#ifndef DATASTRUCT_H
#define DATASTRUCT_H

#include <iostream>
#include <string>

// Формат ввода/вывода: (:key1 0xFF:key2 'A':key3 "Hello":)
// Поля могут идти в любом порядке при вводе.
// key1 — ULL HEX (число)
// key2 — CHR LIT (символ)
// key3 — (строка)
struct DataStruct
{
  unsigned long long key1;
  char key2;
  std::string key3;

  bool operator<(const DataStruct& other) const;
};

// Вспомогательные структуры для перегрузки operator>>

// Ожидает ровно один конкретный символ в потоке
//разделитель
struct DelimiterIO
{
  char exp;
};

// Читает unsigned long long в шестнадцатеричном формате с префиксом 0x/0X  
//hex число
struct UllHexIO
{
  unsigned long long& ref;
};

// Читает символьный литерал вида 'A'
//символ в кавычках
struct CharLitIO
{
  char& ref;
};

// Читает строку в двойных кавычках вида "Hello"
//строка в кавычках
struct StringIO
{
  std::string& ref;
};

// Читает ключевое слово (без кавычек) и сравнивает с ожидаемым
//ключевое слово
struct LabelIO
{
  std::string exp;
};

// Перегрузки оператора побитового сдвига для ввода
std::istream& operator>>(std::istream& in, DelimiterIO&& dest);
std::istream& operator>>(std::istream& in, UllHexIO&& dest);
std::istream& operator>>(std::istream& in, CharLitIO&& dest);
std::istream& operator>>(std::istream& in, StringIO&& dest);
std::istream& operator>>(std::istream& in, LabelIO&& dest);
std::istream& operator>>(std::istream& in, DataStruct& dest);

// Перегрузка оператора побитового сдвига для вывода
std::ostream& operator<<(std::ostream& out, const DataStruct& src);

// Компаратор для std::sort
struct DataStructComparator
{
  bool operator()(const DataStruct& lhs, const DataStruct& rhs) const;
};

#endif // DATASTRUCT_H
