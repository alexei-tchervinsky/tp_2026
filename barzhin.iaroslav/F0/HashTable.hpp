//
// Created by xmdnusr on 04.05.2026.
//

#ifndef SPBSTU_COURSEWORK_HASHTABLE_HPP
#define SPBSTU_COURSEWORK_HASHTABLE_HPP

#include "WordEntry.hpp"

#include <cstddef>
#include <list>
#include <vector>
#include <string>

constexpr std::size_t DEFAULT_TABLE_SIZE = 101; // better to be prime number
constexpr std::size_t HASH_SEED_1 = 0x811c9dc5;
constexpr std::size_t HASH_SEED_2 = 0x5bd1e995;

class HashTable {
public:
  explicit HashTable(std::size_t size = DEFAULT_TABLE_SIZE);

  HashTable(HashTable const&) = delete;
  HashTable(HashTable&&) = delete;
  HashTable& operator=(HashTable const&) = delete;
  HashTable& operator=(HashTable&&) = delete;

  std::size_t getIndex(const std::string& word) const;
  void addWord(const std::string& word);
  bool containsWord(const std::string& word) const;
  int getCount(const std::string& word) const;

  std::size_t getSize() const;
  std::vector<WordEntry>& getBucket(std::size_t idx);

private:
  std::vector<std::vector<WordEntry>> table_;
  std::size_t size_{};
};

#endif //SPBSTU_COURSEWORK_HASHTABLE_HPP
