#include "datastruct.hpp"
#include "stream_guard.hpp"
#include <sstream>
#include <regex>
#include <iomanip>
#include <vector>
#include <cmath>
#include <algorithm>

namespace tchervinsky
{

    static std::string trim(const std::string& str)
    {
        size_t first = str.find_first_not_of(" \t\n\r");
        if (first == std::string::npos) return "";
        size_t last = str.find_last_not_of(" \t\n\r");
        return str.substr(first, last - first + 1);
    }

    static bool parseChar(const std::string& s, char& result)
    {
        std::string trimmed = trim(s);
        if (trimmed.length() == 3 && trimmed[0] == '\'' && trimmed[2] == '\'')
        {
            result = trimmed[1];
            return true;
        }
        return false;
    }

    static bool parseDoubleSci(const std::string& s, double& result)
    {
        std::string trimmed = trim(s);
        std::regex sciRegex(R"(^([+-]?\d+\.\d+)[eE]([+-]?\d+)$)");
        std::smatch match;
        if (std::regex_match(trimmed, match, sciRegex))
        {
            try
            {
                result = std::stod(trimmed);
                return true;
            }
            catch (...)
            {
                return false;
            }
        }
        return false;
    }

    static std::string formatDoubleSci(double value)
    {
        if (std::abs(value) < 1e-10)
        {
            return "1.0e-1";
        }

        int exponent = 0;
        double mantissa = value;

        if (mantissa != 0)
        {
            while (mantissa >= 10.0)
            {
                mantissa /= 10.0;
                exponent++;
            }
            while (mantissa < 1.0)
            {
                mantissa *= 10.0;
                exponent--;
            }
        }

        std::ostringstream oss;
        oss << std::fixed << std::setprecision(1) << mantissa << "e";

        if (exponent > 0)
            oss << "+";
        else if (exponent < 0)
            oss << "-";

        oss << std::abs(exponent);
        return oss.str();
    }

    static std::vector<std::string> splitFields(const std::string& str)
    {
        std::vector<std::string> fields;
        std::string current;
        bool inQuotes = false;
        char quoteChar = '\0';

        for (size_t i = 0; i < str.length(); ++i)
        {
            char c = str[i];

            if (!inQuotes && (c == '"' || c == '\''))
            {
                inQuotes = true;
                quoteChar = c;
                current += c;
            }
            else if (inQuotes && c == quoteChar)
            {
                inQuotes = false;
                quoteChar = '\0';
                current += c;
            }
            else if (!inQuotes && c == ':')
            {
                if (!current.empty())
                {
                    fields.push_back(current);
                    current.clear();
                }
            }
            else
            {
                current += c;
            }
        }

        if (!current.empty())
        {
            fields.push_back(current);
        }

        return fields;
    }

    static bool parseDataStruct(const std::string& line, DataStruct& ds)
    {
        std::string content = trim(line);
        if (content.length() < 2 || content[0] != '(' || content[content.length() - 1] != ')')
            return false;

        content = content.substr(1, content.length() - 2);

        std::vector<std::string> fields = splitFields(content);

        bool hasKey1 = false, hasKey2 = false, hasKey3 = false;
        char key1_val = 0;
        double key2_val = 0.0;
        std::string key3_val;

        for (const auto& f : fields)
        {
            size_t spacePos = f.find(' ');
            if (spacePos == std::string::npos)
                continue;

            std::string fieldName = trim(f.substr(0, spacePos));
            std::string fieldValue = trim(f.substr(spacePos + 1));

            if (fieldName == "key1")
            {
                if (parseChar(fieldValue, key1_val))
                    hasKey1 = true;
            }
            else if (fieldName == "key2")
            {
                if (parseDoubleSci(fieldValue, key2_val))
                    hasKey2 = true;
            }
            else if (fieldName == "key3")
            {
                // Парсинг строки в кавычках
                if (fieldValue.length() >= 2)
                {
                    char first = fieldValue[0];
                    char last = fieldValue[fieldValue.length() - 1];
                    if ((first == '"' && last == '"') || (first == '\'' && last == '\''))
                    {
                        key3_val = fieldValue.substr(1, fieldValue.length() - 2);
                        hasKey3 = true;
                    }
                }
            }
        }

        if (hasKey1 && hasKey2 && hasKey3)
        {
            ds.key1 = key1_val;
            ds.key2 = key2_val;
            ds.key3 = key3_val;
            return true;
        }
        return false;
    }

    std::istream& operator>>(std::istream& in, DataStruct& ds)
    {
        StreamGuard guard(in);
        std::string line;
        while (std::getline(in, line))
        {
            if (parseDataStruct(line, ds))
                break;
        }
        return in;
    }

    std::ostream& operator<<(std::ostream& out, const DataStruct& ds)
    {
        StreamGuard guard(out);
        out << "(:key1 '" << ds.key1 << "':key2 " << formatDoubleSci(ds.key2) << ":key3 \"" << ds.key3 << "\":)";
        return out;
    }

    bool DataStruct::operator<(const DataStruct& other) const
    {
        if (key1 != other.key1)
            return key1 < other.key1;
        if (std::abs(key2 - other.key2) > 1e-10)
            return key2 < other.key2;
        return key3.length() < other.key3.length();
    }

} // namespace tchervinsky

