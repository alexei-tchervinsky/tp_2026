#include "DictionaryHashTable.hpp"
#include <iostream>
#include <stdexcept>
#include <iomanip>

HashEntry::HashEntry() : key(""), state(CellState::EMPTY) {}

DictionaryHashTable::DictionaryHashTable(size_t initialCapacity)
    : capacity(initialCapacity), size(0)
{
  if (initialCapacity == 0)
  {
    throw std::invalid_argument("Error: Initial capacity must be greater than zero.");
  }
  table.resize(capacity);
}

size_t DictionaryHashTable::computeHash(const std::string &word) const
{
  size_t hash = 0;
  const size_t prime = 31;
  for (char ch : word)
  {
    hash = (hash * prime + ch) % capacity;
  }
  return hash;
}

void DictionaryHashTable::resizeAndRehash()
{
  size_t oldCapacity = capacity;
  std::vector<HashEntry> oldTable = table;

  capacity = nextPrime(static_cast<size_t>(oldCapacity * 1.5));
  table = std::vector<HashEntry>(capacity);
  size = 0;

  for (size_t i = 0; i < oldCapacity; ++i)
  {
    if (oldTable[i].state == CellState::OCCUPIED)
    {
      insertEntry(oldTable[i].key, oldTable[i].translations);
    }
  }
}

void DictionaryHashTable::insertEntry(const std::string &word, const TranslationList &list)
{
  size_t hashIndex = computeHash(word);
  size_t i = 0;

  while (i < capacity)
  {
    size_t currentIndex = (hashIndex + i) % capacity;
    if (table[currentIndex].state == CellState::EMPTY || table[currentIndex].state == CellState::DELETED)
    {
      table[currentIndex].key = word;
      table[currentIndex].translations = list;
      table[currentIndex].state = CellState::OCCUPIED;
      size++;
      return;
    }
    i++;
  }
}

void DictionaryHashTable::insert(const std::string &word, const std::string &translation)
{
  if (word.empty())
  {
    throw std::invalid_argument("Error: Word key cannot be empty.");
  }
  if (translation.empty())
  {
    throw std::invalid_argument("Error: Translation value cannot be empty.");
  }

  if (static_cast<double>(size) / capacity >= maxLoadFactor)
  {
    resizeAndRehash();
  }

  size_t hashIndex = computeHash(word);
  size_t i = 0;
  int firstDeletedIndex = -1;

  while (i < capacity)
  {
    size_t currentIndex = (hashIndex + i) % capacity;

    if (table[currentIndex].state == CellState::OCCUPIED)
    {
      if (table[currentIndex].key == word)
      {
        table[currentIndex].translations.insertSorted(translation);
        return;
      }
    }
    else if (table[currentIndex].state == CellState::DELETED)
    {
      if (firstDeletedIndex == -1)
      {
        firstDeletedIndex = static_cast<int>(currentIndex);
      }
    }
    else if (table[currentIndex].state == CellState::EMPTY)
    {
      size_t targetIndex = (firstDeletedIndex != -1) ? static_cast<size_t>(firstDeletedIndex) : currentIndex;

      table[targetIndex].key = word;
      table[targetIndex].translations.clear();
      table[targetIndex].translations.insertSorted(translation);
      table[targetIndex].state = CellState::OCCUPIED;
      size++;
      return;
    }
    i++;
  }
  throw std::runtime_error("Error: Hash table overflow.");
}

const TranslationList *DictionaryHashTable::search(const std::string &word) const
{
  if (word.empty())
  {
    throw std::invalid_argument("Error: Search key cannot be empty.");
  }

  size_t hashIndex = computeHash(word);
  size_t i = 0;

  while (i < capacity)
  {
    size_t currentIndex = (hashIndex + i) % capacity;

    if (table[currentIndex].state == CellState::EMPTY)
    {
      return nullptr;
    }

    if (table[currentIndex].state == CellState::OCCUPIED && table[currentIndex].key == word)
    {
      return &(table[currentIndex].translations);
    }
    i++;
  }
  return nullptr;
}

void DictionaryHashTable::remove(const std::string &word)
{
  if (word.empty())
  {
    throw std::invalid_argument("Error: Delete key cannot be empty.");
  }

  size_t hashIndex = computeHash(word);
  size_t i = 0;

  while (i < capacity)
  {
    size_t currentIndex = (hashIndex + i) % capacity;

    if (table[currentIndex].state == CellState::EMPTY)
    {
      throw std::runtime_error("Error: Word '" + word + "' not found for removal.");
    }

    if (table[currentIndex].state == CellState::OCCUPIED && table[currentIndex].key == word)
    {
      table[currentIndex].state = CellState::DELETED;
      table[currentIndex].key = "";
      table[currentIndex].translations.clear();
      size--;
      return;
    }
    i++;
  }
  throw std::runtime_error("Error: Word '" + word + "' not found for removal.");
}

void DictionaryHashTable::displayTable() const
{
  std::cout << "\n--- Hash Table (Capacity: " << capacity << ", Size: " << size << ") ---\n";
  for (size_t i = 0; i < capacity; ++i)
  {
    std::cout << "Slot " << std::setw(2) << i << ": ";
    if (table[i].state == CellState::OCCUPIED)
    {
      std::cout << "[OCCUPIED] " << table[i].key << " -> ";
      table[i].translations.print();
    }
    else if (table[i].state == CellState::DELETED)
    {
      std::cout << "[DELETED]";
    }
    else
    {
      std::cout << "[EMPTY]";
    }
    std::cout << "\n";
  }
  std::cout << "---------------------------------------------------------\n";
}

bool DictionaryHashTable::isPrime(size_t n) const
{
  if (n <= 1)
    return false;
  if (n <= 3)
    return true;

  if (n % 2 == 0 || n % 3 == 0)
    return false;

  for (size_t i = 5; i * i <= n; i += 6)
  {
    if (n % i == 0 || n % (i + 2) == 0)
    {
      return false;
    }
  }
  return true;
}

size_t DictionaryHashTable::nextPrime(size_t n) const
{
  if (n <= 2)
    return 2;

  size_t prime = n;
  if (prime % 2 == 0)
  {
    prime++;
  }

  while (!isPrime(prime))
  {
    prime += 2;
  }
  return prime;
}
