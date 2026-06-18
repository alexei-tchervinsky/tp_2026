#ifndef DICTIONARYHASHTABLE_HPP
#define DICTIONARYHASHTABLE_HPP
#include "TranslationList.hpp"
#include <string>
#include <vector>

enum class CellState
{
  EMPTY,
  OCCUPIED,
  DELETED
};

struct HashEntry
{
  std::string key;
  TranslationList translations;
  CellState state;

  HashEntry();
};

class DictionaryHashTable
{
private:
  std::vector<HashEntry> table;
  size_t capacity;
  size_t size;
  const double maxLoadFactor = 0.7;

  size_t computeHash(const std::string &word) const;
  void resizeAndRehash();
  void insertEntry(const std::string &word, const TranslationList &list);

public:
  explicit DictionaryHashTable(size_t initialCapacity = 11);

  void insert(const std::string &word, const std::string &translation);
  const TranslationList *search(const std::string &word) const;
  void remove(const std::string &word);
  void displayTable() const;

  bool isPrime(size_t n) const;
  size_t nextPrime(size_t n) const;
};

#endif
