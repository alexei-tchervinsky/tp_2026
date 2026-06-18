#include "DataStruct.hpp"
#include "Delimiters.hpp"
#include <iomanip>
#include <sstream>
#include <string>

bool compareDataStruct(const DataStruct& lhs, const DataStruct& rhs)
{
    if (lhs.key1 != rhs.key1)
        return lhs.key1 < rhs.key1;
    if (lhs.key2 != rhs.key2)
        return lhs.key2 < rhs.key2;
    return lhs.key3.length() < rhs.key3.length();
}

// Читает токен до ':'
static bool readToken(std::istream& in, std::string& token)
{
    token.clear();
    // Пропустить leading пробелы вручную
    char c = 0;
    while (in.get(c) && c == ' ') {}
    if (!in) return false;
    // Первый непробельный символ
    token += c;
    // Читаем до ':' или пробела
    while (in.get(c) && c != ':' && c != ' ')
        token += c;
    // Если остановились на ':', вернуть его обратно
    if (in && c == ':')
        in.putback(c);
    return !token.empty();
}

// Проверяет что строка — валидный DBL SCI формат: X.Xe±N без суффиксов d/D
static bool parseDblSci(const std::string& token, double& val)
{
    if (token.empty()) return false;
    // Не должно быть суффикса d/D (это DBL LIT)
    char last = token.back();
    if (last == 'd' || last == 'D') return false;
    // Должен содержать e или E
    size_t epos = token.find_first_of("eE");
    if (epos == std::string::npos) return false;
    // Мантисса должна содержать точку
    std::string mantissa = token.substr(0, epos);
    if (mantissa.find('.') == std::string::npos) return false;
    // Мантисса должна иметь цифры до и после точки
    size_t dotpos = mantissa.find('.');
    // до точки: либо цифра, либо '-' + цифра
    size_t start = (mantissa[0] == '-') ? 1 : 0;
    if (dotpos == start) return false;        // нет цифр до точки
    if (dotpos == mantissa.size() - 1) return false; // нет цифр после точки
    // Парсим
    std::istringstream ss(token);
    ss >> val;
    return !ss.fail() && ss.eof();
}

std::istream& operator>>(std::istream& in, DataStruct& dest)
{
    std::istream::sentry guard(in);
    if (!guard)
        return in;

    DataStruct temp{0.0, '\0', ""};
    bool has_key1 = false;
    bool has_key2 = false;
    bool has_key3 = false;

    // Читаем '('
    in >> DelimiterChar{'('};
    if (!in) return in;

    for (int i = 0; i < 3; ++i)
    {
        // Читаем ':'
        in >> DelimiterChar{':'};
        if (!in) return in;

        // Читаем имя ключа — без пропуска пробелов (после ':' сразу имя)
        std::string key_name;
        char c = 0;
        while (in.get(c) && c != ' ' && c != ':')
            key_name += c;
        // c == ' ' — нормально, значение идёт дальше
        // c == ':' — пустое значение, ошибка
        if (!in || c == ':')
        {
            in.setstate(std::ios_base::failbit);
            return in;
        }

        if (key_name == "key1")
        {
            if (has_key1) { in.setstate(std::ios_base::failbit); return in; }
            std::string token;
            if (!readToken(in, token))
            { in.setstate(std::ios_base::failbit); return in; }
            double val = 0.0;
            if (!parseDblSci(token, val))
            { in.setstate(std::ios_base::failbit); return in; }
            temp.key1 = val;
            has_key1 = true;
        }
        else if (key_name == "key2")
        {
            if (has_key2) { in.setstate(std::ios_base::failbit); return in; }
            // Формат: 'X' — кавычки примыкают к ':'
            // После пробела (уже съеден) читаем: ' char '
            char q1 = 0, ch = 0, q2 = 0;
            if (!in.get(q1) || q1 != '\'')
            { in.setstate(std::ios_base::failbit); return in; }
            if (!in.get(ch))
            { in.setstate(std::ios_base::failbit); return in; }
            if (!in.get(q2) || q2 != '\'')
            { in.setstate(std::ios_base::failbit); return in; }
            temp.key2 = ch;
            has_key2 = true;
        }
        else if (key_name == "key3")
        {
            if (has_key3) { in.setstate(std::ios_base::failbit); return in; }
            // Формат: "строка" — кавычка примыкает к ':'
            char quote = 0;
            if (!in.get(quote) || quote != '"')
            { in.setstate(std::ios_base::failbit); return in; }
            std::string str;
            if (!std::getline(in, str, '"'))
            { in.setstate(std::ios_base::failbit); return in; }
            temp.key3 = str;
            has_key3 = true;
        }
        else
        {
            in.setstate(std::ios_base::failbit);
            return in;
        }
    }

    // Читаем ':)'
    in >> DelimiterChar{':'};
    if (!in) return in;
    in >> DelimiterChar{')'};
    if (!in) return in;

    if (has_key1 && has_key2 && has_key3)
        dest = temp;
    else
        in.setstate(std::ios_base::failbit);

    return in;
}

std::ostream& operator<<(std::ostream& out, const DataStruct& src)
{
    std::ostream::sentry guard(out);
    if (!guard)
        return out;

    // DBL SCI: мантисса с точкой, e в нижнем регистре, precision(1)
    std::ostringstream ss;
    ss << std::scientific << std::setprecision(1) << src.key1;
    std::string s = ss.str();
    // std::scientific выводит e+01, нам нужен e+1 —
    // Ищем 'e' или 'E'
    for (char& ch : s) if (ch == 'E') ch = 'e';
    // Убрать ведущий ноль в экспоненте: e+01 -> e+1, e-02 -> e-2
    size_t epos = s.find('e');
    if (epos != std::string::npos && epos + 2 < s.size())
    {
        // s[epos+1] — знак (+/-), s[epos+2..] — цифры экспоненты
        std::string exp_part = s.substr(epos + 2);
        // Убрать ведущие нули
        size_t nz = exp_part.find_first_not_of('0');
        if (nz == std::string::npos) exp_part = "0";
        else exp_part = exp_part.substr(nz);
        s = s.substr(0, epos + 2) + exp_part;
    }

    out << "(:key1 " << s;
    out << ":key2 '" << src.key2 << "'";
    out << ":key3 \"" << src.key3 << "\":)";
    return out;
}
