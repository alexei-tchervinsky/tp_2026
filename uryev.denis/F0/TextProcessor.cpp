#include "TextProcessor.hpp"
#include <fstream>
#include <cctype>

std::string TextProcessor::cleanWord(const std::string &raw_word) const
{
  std::string clean_str = "";

  for (char ch : raw_word)
  {
    unsigned char uc = static_cast<unsigned char>(ch);

    if (std::isalpha(uc) || std::isdigit(uc) || uc > 127)
    {
      clean_str += static_cast<char>(std::tolower(uc));
    }
  }
  return clean_str;
}

bool TextProcessor::processFile(const std::string &filename, std::unordered_map<std::string, int> &table)
{
  std::ifstream file(filename);

  if (!file.is_open())
  {
    return false;
  }

  std::string current_word;
  while (file >> current_word)
  {
    std::string cleaned = cleanWord(current_word);

    if (!cleaned.empty())
    {
      table[cleaned]++;
    }
  }

  file.close();
  return true;
}
