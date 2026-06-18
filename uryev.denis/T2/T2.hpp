#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>
#include <iomanip>
#include <cmath>
#include <sstream>

std::string formatScientific(const double data) {
  std::ostringstream oss;
  oss << std::scientific << std::setprecision(1) << std::nouppercase<< data;
  std::string str = oss.str();

  size_t e_pos = str.find('e');
  if (e_pos != std::string::npos) {
    if (e_pos + 2 < str.size() && str[e_pos + 2] == '0') {
      str.erase(e_pos + 2, 1);
    }
  }
  return str;
}

struct DataStruct {
    double key1;
    unsigned long long key2;
    std::string key3;
};

struct Delimiter {
    char expected;
};

std::istream& operator>>(std::istream& in, Delimiter&& dest) {
    std::istream::sentry sentry(in);
    if (!sentry) return in;
    char c;
    in >> c;
    if (std::tolower(c) != std::tolower(dest.expected)) {
        in.setstate(std::ios::failbit);
    }
    return in;
}

// Перегрузка оператора ввода согласно заданию
std::istream& operator>>(std::istream& in, DataStruct& dest) {
  std::istream::sentry sentry(in);
  if (!sentry) return in;

  DataStruct temp{ 0.0, 0, "" };
  bool has_key1 = false, has_key2 = false, has_key3 = false;

  // 1. Начало (
  if (!(in >> Delimiter{ '(' })) return in;

  for (int i = 0; i < 3; ++i) {
    // 2. Читаем двоеточие перед ключом
    if (!(in >> Delimiter{ ':' })) return in;

    std::string label;
    // Читаем название ключа (оно должно быть строго key1, key2 или key3)
    // Если двоеточие приклеено к ключу, мы его уже считали выше
    if (!(in >> label)) return in;

    if (label == "key1") {
      // Явно указываем десятичную систему, чтобы не влиял hex от key2
      if (!(in >> std::dec >> temp.key1)) return in;
      has_key1 = true;
    }
    else if (label == "key2") {
      // Читаем префикс 0x вручную
      char zero, x;
      if (!(in >> zero >> x) || zero != '0' || std::tolower(x) != 'x') {
        in.setstate(std::ios::failbit);
        return in;
      }
      // Читаем число в HEX, а потом СРАЗУ сбрасываем в DEC
      if (!(in >> std::hex >> temp.key2)) return in;
      in >> std::dec;
      has_key2 = true;
    }
    else if (label == "key3") {
      // Используем std::quoted — он решит проблему с "Data with :"
      if (!(in >> std::quoted(temp.key3))) return in;
      has_key3 = true;
    }
  }

  // 3. Последнее двоеточие и закрывающая скобка :)
  if (!(in >> Delimiter{ ':' } >> Delimiter{ ')' })) return in;

  if (has_key1 && has_key2 && has_key3) {
    dest = temp;
  }
  return in;
}

// Перегрузка оператора вывода согласно заданию
std::ostream& operator<<(std::ostream& out, const DataStruct& src) {
  std::ostream::sentry sentry(out);
  if (!sentry) return out;

  // Сохраняем состояние флагов
  std::ios_base::fmtflags f(out.flags());

  out << "(:key1 " << formatScientific(src.key1);

  // Вывод key2 (в HEX и одинарных кавычках, как в твоем фрагменте)
  out << ":key2 0x" << std::hex << std::uppercase << src.key2;

  // Вывод key3
  out << ":key3 \"" << src.key3 << "\":)";

  out.flags(f);
  return out;
}
