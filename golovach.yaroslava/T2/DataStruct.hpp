#ifndef DATASTRUCT_H
#define DATASTRUCT_H

#include <iostream>
#include <string>

// key1 — DBL SCI (вещественное число в научной нотации)
// key2 — CHR LIT (символ в одинарных кавычках)
// key3 — STR (строка в двойных кавычках)
struct DataStruct
{
  double key1;
  char key2;
  std::string key3;

  bool operator<(const DataStruct& other) const;
};

struct DelimiterIO
{
  char exp;
};

struct DblSciIO
{
  double& ref;
};

struct CharLitIO
{
  char& ref;
};

struct StringIO
{
  std::string& ref;
};

std::istream& operator>>(std::istream& in, DelimiterIO&& dest);
std::istream& operator>>(std::istream& in, DblSciIO&& dest);
std::istream& operator>>(std::istream& in, CharLitIO&& dest);
std::istream& operator>>(std::istream& in, StringIO&& dest);
std::istream& operator>>(std::istream& in, DataStruct& dest);

std::ostream& operator<<(std::ostream& out, const DataStruct& src);

struct DataStructComparator
{
  bool operator()(const DataStruct& lhs, const DataStruct& rhs) const;
};

#endif // DATASTRUCT_H#ifndef DATASTRUCT_H
#define DATASTRUCT_H

#include <iostream>
#include <string>

// Поля могут идти в любом порядке при вводе.
// key1 — DBL SCI (вещественное число в научной нотации)
// key2 — CHR LIT (символ в одинарных кавычках)
struct DataStruct
{
  double key1;
  char key2;

  bool operator<(const DataStruct& other) const;
};

// Вспомогательные структуры для перегрузки operator>>

// Ожидает ровно один конкретный символ в потоке
struct DelimiterIO
{
  char exp;
};


struct DblSciIO
{
  double& ref;
};


struct CharLitIO
{
  char& ref;
};


std::istream& operator>>(std::istream& in, DelimiterIO&& dest);
std::istream& operator>>(std::istream& in, DblSciIO&& dest);
std::istream& operator>>(std::istream& in, CharLitIO&& dest);
std::istream& operator>>(std::istream& in, DataStruct& dest);


std::ostream& operator<<(std::ostream& out, const DataStruct& src);

// Компаратор для std::sort
struct DataStructComparator
{
  bool operator()(const DataStruct& lhs, const DataStruct& rhs) const;
};

#endif // DATASTRUCT_H
