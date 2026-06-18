#include "CrossReference.hpp"

#include <cctype>
#include <fstream>
#include <ostream>
#include <stdexcept>
#include <string>

void CrossReference::clear()
{
  dictionary_.clear();
}

std::string CrossReference::normalizeWord(const std::string& word)
{
  std::string result;

  for (char ch : word)
  {
    const unsigned char symbol = static_cast< unsigned char >(ch);

    if (std::isalnum(symbol))
    {
      result.push_back(
        static_cast< char >(std::tolower(symbol))
      );
    }
  }

  return result;
}

void CrossReference::addWord(const std::string& word, int lineNumber)
{
  if (lineNumber <= 0)
  {
    throw std::invalid_argument("Line number must be positive");
  }

  const std::string normalized = normalizeWord(word);

  if (normalized.empty())
  {
    throw std::invalid_argument("Word must not be empty");
  }

  dictionary_[normalized].insert(lineNumber);
}

bool CrossReference::contains(const std::string& word) const
{
  const std::string normalized = normalizeWord(word);

  if (normalized.empty())
  {
    return false;
  }

  return dictionary_.find(normalized) != dictionary_.end();
}

void CrossReference::removeWord(const std::string& word)
{
  const std::string normalized = normalizeWord(word);

  if (!normalized.empty())
  {
    dictionary_.erase(normalized);
  }
}

void CrossReference::printWord(const std::string& word, std::ostream& out) const
{
  const std::string normalized = normalizeWord(word);

  const auto iterator = dictionary_.find(normalized);

  if (iterator == dictionary_.end())
  {
    out << normalized << " : not found\n";
    return;
  }

  out << iterator->first << " :";

  for (int lineNumber : iterator->second)
  {
    out << " " << lineNumber;
  }

  out << "\n";
}

void CrossReference::printAll(std::ostream& out) const
{
  if (dictionary_.empty())
  {
    out << "The dictionary is empty.\n";
    return;
  }

  for (const auto& entry : dictionary_)
  {
    out << entry.first << " :";

    for (int lineNumber : entry.second)
    {
      out << " " << lineNumber;
    }

    out << "\n";
  }
}

void CrossReference::insertWordsFromLine(const std::string& line, int lineNumber)
{
  std::string currentWord;

  for (std::size_t i = 0; i <= line.size(); ++i)
  {
    const char ch = (i < line.size()) ? line[i] : ' ';
    const unsigned char symbol = static_cast< unsigned char >(ch);

    if (std::isalnum(symbol))
    {
      currentWord.push_back(
        static_cast< char >(std::tolower(symbol))
      );
    }
    else if (!currentWord.empty())
    {
      dictionary_[currentWord].insert(lineNumber);
      currentWord.clear();
    }
  }
}

bool CrossReference::loadFromFile(
  const std::string& fileName,
  std::ostream& numberedTextOut
)
{
  std::ifstream input(fileName);

  if (!input)
  {
    return false;
  }

  clear();

  std::string line;
  int lineNumber = 0;

  while (std::getline(input, line))
  {
    ++lineNumber;

    numberedTextOut << lineNumber << ": " << line << "\n";

    insertWordsFromLine(line, lineNumber);
  }

  return true;
}
