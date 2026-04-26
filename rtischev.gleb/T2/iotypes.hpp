#ifndef IOTYPES_H
#define IOTYPES_H

#include <iostream>
#include <string>
#include <utility>


// структура разделителя
struct DelimetrIO
{
    char exp;
};

// структура 16-ричного числа
struct UllHexIO {
    unsigned long long& ref;
};

// стуктура рациональной дроби
struct RationalIO
{
    std::pair<long long, unsigned long long>& ref;
};

// структура строки
struct StringIO
{
    std::string& ref;
};

// структура ключа
struct KeyIO
{
    std::string& ref;
};

// операторы перегрузки

// Перегрузка оператора ввода для структуры DelimetrIO
std::istream& operator>>(std::istream& in, DelimetrIO&& dest);
// Перегрузка оператора ввода для структуры UllHexIO
std::istream& operator>>(std::istream& in, UllHexIO&& dest);
// Перегрузка оператора ввода для структуры RationalIO
std::istream& operator>>(std::istream& in, RationalIO&& dest);
// Перегрузка оператора ввода для структуры StringIO
std::istream& operator>>(std::istream& in, StringIO&& dest);
// Перегрузка оператора ввода для структуры KeyIO
std::istream& operator>>(std::istream& in, KeyIO&& dest);


#endif
