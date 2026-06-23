#ifndef DATA_STRUCT_HPP
#define DATA_STRUCT_HPP

#include <string>
#include <iostream>

struct DataStruct
{
    double key1;  // хранит вещественное число
    char key2;    // символ
    std::string key3;  //строки в кавычках
};

// Вспомогательные структуры для перегрузки operator>>

struct DelimiterIO
{
    char exp;  // Хранит ожидаемый одиночный символ-разделитель
};

struct DoubleSciIO
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

// Объявления операторов ввода/вывода
std::istream& operator>>(std::istream& in, DelimiterIO&& dest);
std::istream& operator>>(std::istream& in, DoubleSciIO&& dest);
std::istream& operator>>(std::istream& in, CharLitIO&& dest);
std::istream& operator>>(std::istream& in, StringIO&& dest);

std::istream& operator>>(std::istream& in, DataStruct& dest);
std::ostream& operator<<(std::ostream& out, const DataStruct& src);

//компаратор для сортировки данных в std::sort
bool compareDataStruct(const DataStruct& lhs, const DataStruct& rhs);

#endif
