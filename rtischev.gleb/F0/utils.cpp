#include "utils.hpp"
#include <cctype>

std::string toLower(const std::string &str)
{
    std::string result = "";
    for (char c : str)
    {
        result += static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
    }
    return result;
}
