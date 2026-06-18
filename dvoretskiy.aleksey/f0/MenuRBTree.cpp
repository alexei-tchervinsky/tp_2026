#include "MenuRBTree.hpp"

#include <fstream>
#include <iomanip>
#include <iostream>

#ifdef _WIN32
#include <Windows.h>
#endif

namespace
{
  constexpr int IndentTerm = 4;

  void SetConsoleColor(const Color color)
  {
#ifdef _WIN32
    constexpr int Background = 7;

    const int textColor =
      color == Color::Red ? 4 : 0;

    HANDLE output =
      GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleTextAttribute(
      output,
      static_cast<WORD>(
        (Background << 4) | textColor));
#else
    (void)color;
#endif
  }

  void ResetConsoleColor()
  {
#ifdef _WIN32
    constexpr int Background = 7;

    HANDLE output =
      GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleTextAttribute(
      output,
      static_cast<WORD>(
        Background << 4));
#endif
  }

  void PrintTranslations(const Node* node)
  {
    if (node == nullptr ||
      node->Translations == nullptr)
    {
      return;
    }

    for (const std::string& translation :
      *node->Translations)
    {
      std::cout
        << " - "
        << translation
        << '\n';
    }
  }

  bool IsUtf8RussianWord(
    const std::string& word)
  {
    std::size_t index = 0;

    while (index < word.size())
    {
      if (index + 1 >= word.size())
      {
        return false;
      }

      const unsigned char first =
        static_cast<unsigned char>(
          word[index]);

      const unsigned char second =
        static_cast<unsigned char>(
          word[index + 1]);

      const bool russianLetter =
        (first == 0xD0 &&
          second >= 0x90 &&
          second <= 0xBF) ||
        (first == 0xD1 &&
          second >= 0x80 &&
          second <= 0x8F);

      if (!russianLetter)
      {
        return false;
      }

      index += 2;
    }

    return true;
  }
}

int GetElementConsoleRBTree()
{
  while (true)
  {
    std::string input;

    std::cout << "Enter menu value: ";
    std::getline(std::cin, input);

    try
    {
      std::size_t length = 0;

      const int value =
        std::stoi(input, &length);

      if (length == input.length())
      {
        return value;
      }
    }
    catch (const std::exception&)
    {
    }

    std::cout
      << "Incorrect menu value.\n";
  }
}

std::string GetWordConsoleRBTree()
{
  while (true)
  {
    std::string word;
    std::getline(std::cin, word);

    if (!word.empty())
    {
      return word;
    }

    std::cout
      << "Empty input. Try again: ";
  }
}

bool IsEnglishWord(
  const std::string& word)
{
  if (word.empty())
  {
    return false;
  }

  for (const unsigned char symbol : word)
  {
    const bool englishLetter =
      (symbol >= 'A' && symbol <= 'Z') ||
      (symbol >= 'a' && symbol <= 'z');

    if (!englishLetter)
    {
      return false;
    }
  }

  return true;
}

bool IsRussianWord(
  const std::string& word)
{
  if (word.empty())
  {
    return false;
  }

  bool isCp1251 = true;

  for (const unsigned char symbol : word)
  {
    const bool russianLetter =
      (symbol >= 192 && symbol <= 255) ||
      symbol == 168 ||
      symbol == 184;

    if (!russianLetter)
    {
      isCp1251 = false;
      break;
    }
  }

  return isCp1251 ||
    IsUtf8RussianWord(word);
}

void PrintTree(
  const Node* node,
  const int indent)
{
  if (node == nullptr)
  {
    return;
  }

  PrintTree(
    node->Right,
    indent + IndentTerm);

  if (indent > 0)
  {
    std::cout
      << std::setw(indent)
      << ' ';
  }

  SetConsoleColor(node->NodeColor);

  std::cout << node->EnglishWord;

  ResetConsoleColor();

  std::cout << '\n';

  PrintTree(
    node->Left,
    indent + IndentTerm);
}

void LoadFromFile(
  Node*& root,
  const std::string& fileName)
{
  std::ifstream file(fileName);

  if (!file)
  {
    std::cout << "File not found.\n";
    return;
  }

  std::string command;

  while (file >> command)
  {
    if (command == "add")
    {
      std::string word;
      std::string translation;

      if (!(file >> word >> translation))
      {
        break;
      }

      if (IsEnglishWord(word) &&
        IsRussianWord(translation))
      {
        InsertValue(
          root,
          word,
          translation);
      }
    }
    else if (command == "find")
    {
      std::string word;

      if (!(file >> word))
      {
        break;
      }

      Node* found =
        Find(root, word);

      if (found == nullptr)
      {
        std::cout
          << "Word not found: "
          << word
          << '\n';
      }
      else
      {
        std::cout
          << found->EnglishWord
          << "\nTranslations:\n";

        PrintTranslations(found);
      }
    }
    else if (command == "remove_word")
    {
      std::string word;

      if (!(file >> word))
      {
        break;
      }

      DeleteValue(root, word);
    }
    else if (
      command == "remove_translation")
    {
      std::string word;
      std::string translation;

      if (!(file >> word >> translation))
      {
        break;
      }

      DeleteTranslation(
        root,
        word,
        translation);
    }
  }

  std::cout << "Test data loaded.\n";
}

void LoadWordsFromFile(
  Node*& root,
  const std::string& fileName)
{
  std::ifstream file(fileName);

  if (!file)
  {
    std::cout << "File not found.\n";
    return;
  }

  std::string word;
  std::string translation;

  while (file >> word >> translation)
  {
    if (!IsEnglishWord(word))
    {
      std::cout
        << "Incorrect English word: "
        << word
        << '\n';

      continue;
    }

    if (!IsRussianWord(translation))
    {
      std::cout
        << "Incorrect Russian translation: "
        << translation
        << '\n';

      continue;
    }

    InsertValue(
      root,
      word,
      translation);
  }

  std::cout << "Words loaded.\n";
}

void Menu(RBTree* tree)
{
  if (tree == nullptr)
  {
    return;
  }

  while (true)
  {
    PrintTree(tree->Root, 0);

    std::cout
      << "\n1 - Add\n"
      << "2 - Remove word\n"
      << "3 - Remove translation\n"
      << "4 - Find\n"
      << "5 - Load command file\n"
      << "6 - Load words file\n"
      << "7 - Exit\n";

    const auto option =
      static_cast<MenuRBTreeOption>(
        GetElementConsoleRBTree());

    switch (option)
    {
    case MenuRBTreeOption::Add:
    {
      std::cout
        << "Enter English word: ";

      const std::string word =
        GetWordConsoleRBTree();

      std::cout
        << "Enter Russian translation: ";

      const std::string translation =
        GetWordConsoleRBTree();

      if (!IsEnglishWord(word))
      {
        std::cout
          << "Only English letters "
          << "are allowed.\n";
      }
      else if (!IsRussianWord(translation))
      {
        std::cout
          << "Only Russian letters "
          << "are allowed.\n";
      }
      else
      {
        InsertValue(
          tree->Root,
          word,
          translation);
      }

      break;
    }

    case MenuRBTreeOption::RemoveWord:
    {
      std::cout
        << "Enter English word: ";

      const std::string word =
        GetWordConsoleRBTree();

      if (DeleteValue(tree->Root, word))
      {
        std::cout << "Word deleted.\n";
      }
      else
      {
        std::cout << "Word not found.\n";
      }

      break;
    }

    case MenuRBTreeOption::RemoveTranslation:
    {
      std::cout
        << "Enter English word: ";

      const std::string word =
        GetWordConsoleRBTree();

      std::cout
        << "Enter Russian translation: ";

      const std::string translation =
        GetWordConsoleRBTree();

      if (DeleteTranslation(
        tree->Root,
        word,
        translation))
      {
        std::cout
          << "Translation deleted.\n";
      }
      else
      {
        std::cout
          << "Word or translation "
          << "not found.\n";
      }

      break;
    }

    case MenuRBTreeOption::Find:
    {
      std::cout
        << "Enter English word: ";

      const std::string word =
        GetWordConsoleRBTree();

      Node* found =
        Find(tree->Root, word);

      if (found == nullptr)
      {
        std::cout
          << "Word not found.\n";
      }
      else
      {
        std::cout
          << found->EnglishWord
          << "\nTranslations:\n";

        PrintTranslations(found);
      }

      break;
    }

    case MenuRBTreeOption::LoadCommandFile:
    {
      std::cout << "Enter file name: ";

      LoadFromFile(
        tree->Root,
        GetWordConsoleRBTree());

      break;
    }

    case MenuRBTreeOption::LoadWordsFile:
    {
      std::cout << "Enter file name: ";

      LoadWordsFromFile(
        tree->Root,
        GetWordConsoleRBTree());

      break;
    }

    case MenuRBTreeOption::Exit:
    {
      FreeTree(tree->Root);
      return;
    }

    default:
    {
      std::cout << "Invalid value.\n";
      break;
    }
    }
  }
}
