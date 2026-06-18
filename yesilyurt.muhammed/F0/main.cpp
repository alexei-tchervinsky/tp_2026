#include "CrossReference.hpp"

#include <iostream>
#include <sstream>
#include <string>

namespace
{
  std::string trimLeft(const std::string& text)
  {
    const std::size_t position = text.find_first_not_of(" \t");

    if (position == std::string::npos)
    {
      return "";
    }

    return text.substr(position);
  }

  bool hasExtraArguments(std::istringstream& stream)
  {
    std::string extra;
    return static_cast< bool >(stream >> extra);
  }

  void printHelp()
  {
    std::cout
      << "Commands:\n"
      << "  LOAD <file_name>\n"
      << "  ADD <word> <line_number>\n"
      << "  FIND <word>\n"
      << "  PRINT_WORD <word>\n"
      << "  REMOVE <word>\n"
      << "  PRINT\n"
      << "  CLEAR\n"
      << "  HELP\n";
  }
}

int main()
{
  CrossReference dictionary;

  std::string line;

  while (std::getline(std::cin, line))
  {
    std::istringstream stream(line);

    std::string command;
    stream >> command;

    if (command.empty())
    {
      continue;
    }

    if (command == "LOAD")
    {
      std::string fileName;
      std::getline(stream, fileName);

      fileName = trimLeft(fileName);

      if (fileName.empty())
      {
        std::cout << "<INVALID COMMAND>\n";
        continue;
      }

      if (!dictionary.loadFromFile(fileName, std::cout))
      {
        std::cout << "<CANNOT OPEN FILE>\n";
        continue;
      }

      std::cout << "<OK>\n";
    }
    else if (command == "ADD")
    {
      std::string word;
      int lineNumber = 0;

      if (!(stream >> word >> lineNumber) || hasExtraArguments(stream))
      {
        std::cout << "<INVALID COMMAND>\n";
        continue;
      }

      try
      {
        dictionary.addWord(word, lineNumber);
        std::cout << "<OK>\n";
      }
      catch (const std::exception&)
      {
        std::cout << "<INVALID COMMAND>\n";
      }
    }
    else if (command == "FIND")
    {
      std::string word;

      if (!(stream >> word) || hasExtraArguments(stream))
      {
        std::cout << "<INVALID COMMAND>\n";
        continue;
      }

      std::cout
        << (dictionary.contains(word) ? "<TRUE>" : "<FALSE>")
        << "\n";
    }
    else if (command == "PRINT_WORD")
    {
      std::string word;

      if (!(stream >> word) || hasExtraArguments(stream))
      {
        std::cout << "<INVALID COMMAND>\n";
        continue;
      }

      dictionary.printWord(word, std::cout);
    }
    else if (command == "REMOVE")
    {
      std::string word;

      if (!(stream >> word) || hasExtraArguments(stream))
      {
        std::cout << "<INVALID COMMAND>\n";
        continue;
      }

      dictionary.removeWord(word);
      std::cout << "<OK>\n";
    }
    else if (command == "PRINT")
    {
      if (hasExtraArguments(stream))
      {
        std::cout << "<INVALID COMMAND>\n";
        continue;
      }

      dictionary.printAll(std::cout);
    }
    else if (command == "CLEAR")
    {
      if (hasExtraArguments(stream))
      {
        std::cout << "<INVALID COMMAND>\n";
        continue;
      }

      dictionary.clear();
      std::cout << "<OK>\n";
    }
    else if (command == "HELP")
    {
      if (hasExtraArguments(stream))
      {
        std::cout << "<INVALID COMMAND>\n";
        continue;
      }

      printHelp();
    }
    else
    {
      std::cout << "<INVALID COMMAND>\n";
    }
  }

  return 0;
}
