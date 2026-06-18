#ifndef TEXTPROCESSOR_HPP
#define TEXTPROCESSOR_HPP

#include "HashTable.hpp"

#include <string>

class TextProcessor
{
public:
    static int processFile(const std::string& filePath, HashTable& hashTable);

private:
    static std::string normalise_(const std::string& token);
};

#endif // TEXTPROCESSOR_HPP
