#include "TextProcessor.hpp"

#include <fstream>
#include <stdexcept>
#include <cctype>

std::string TextProcessor::normalise_(const std::string& token)
{
    std::string result;
    size_t i = 0;

    while (i < token.size())
    {
        unsigned char c = static_cast<unsigned char>(token[i]);

        // English letters and ASCII symbols.
        if (c < 0x80)
        {
            if (std::isalpha(c))
                result += static_cast<char>(std::tolower(c));
            ++i;
        }
        // Multi-byte symbols (UTF-8).
        else
        {
            // Check whether a byte pair is available.
            if (i + 1 < token.size())
            {
                unsigned char c1 = static_cast<unsigned char>(token[i]);
                unsigned char c2 = static_cast<unsigned char>(token[i + 1]);

                // Handle uppercase Russian letters.
                if (c1 == 0xD0)
                {
                    if (c2 >= 0x90 && c2 <= 0x9F) // A - P (Cyrillic uppercase)
                    {
                        result += static_cast<char>(0xD0);
                        result += static_cast<char>(c2 + 0x20);
                        i += 2;
                        continue;
                    }
                    else if (c2 >= 0xA0 && c2 <= 0xAF) // R - Ya (Cyrillic uppercase)
                    {
                        result += static_cast<char>(0xD1);
                        result += static_cast<char>(c2 - 0x20);
                        i += 2;
                        continue;
                    }
                    else if (c2 == 0x81) // Yo (Cyrillic Yo uppercase)
                    {
                        result += static_cast<char>(0xD1);
                        result += static_cast<char>(0x91);
                        i += 2;
                        continue;
                    }
                }

                // Keep lowercase Cyrillic letters (UTF-8 lead bytes 0xD0 or 0xD1).
                // Quotation marks and em-dash (0xC2, 0xE2) are excluded by this check.
                if (c1 == 0xD0 || c1 == 0xD1)
                {
                    result += token[i++];
                    while (i < token.size() &&
                        (static_cast<unsigned char>(token[i]) & 0xC0) == 0x80)
                    {
                        result += token[i++];
                    }
                    continue;
                }
            }

            // Skip non-letter UTF-8 characters (dashes, quotes, etc.).
            i++;
            while (i < token.size() &&
                (static_cast<unsigned char>(token[i]) & 0xC0) == 0x80)
            {
                i++;
            }
        }
    }

    return result;
}

int TextProcessor::processFile(const std::string& filePath,
    HashTable& hashTable)
{
    if (filePath.empty())
        throw std::runtime_error("File path must not be empty.");

    std::ifstream file(filePath);
    if (!file.is_open())
        throw std::runtime_error("Cannot open file: " + filePath);

    std::string token;
    int total = 0;

    while (file >> token)
    {
        std::string word = normalise_(token);
        if (!word.empty())
        {
            hashTable.insert(word);
            ++total;
        }
    }

    return total;
}
