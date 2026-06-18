//
// Created by xmdnusr on 12.05.2026.
//

#include "HashTable.hpp"
#include "utils.hpp"

#include <cstdint>

HashTable::HashTable(std::size_t size) : size_(size) {
  table_.resize(size_);
}

std::size_t HashTable::getIndex(const std::string& word) const {
  std::size_t h = HASH_SEED_1;
  for (char c : word) {
    h ^= static_cast<uint8_t>(c);
    h *= HASH_SEED_2;
  }
  return h % size_;
}

std::size_t HashTable::getSize() const {
  return size_;
}

std::vector<WordEntry>& HashTable::getBucket(std::size_t idx) {
  return table_[idx];
}

void HashTable::addWord(const std::string& word) {
  const std::size_t idx = getIndex(word);
  std::vector<WordEntry>& bucket = table_[idx];
  for (auto& entry : bucket) {
    if (entry.word_ == word) {
      ++entry.count_;
      return;
    }
  }
  bucket.push_back({word, 1});
}

bool HashTable::containsWord(const std::string& word) const {
  const std::size_t idx = getIndex(word);
  const std::vector<WordEntry>& bucket = table_[idx];
  return std::any_of(bucket.begin(), bucket.end(),
                     [&word](const WordEntry& entry) {
                       return entry.word_ == word;
                     });
}

int HashTable::getCount(const std::string& word) const {
  const std::size_t idx = getIndex(word);
  const std::vector<WordEntry>& bucket = table_[idx];

  for (const auto& entry : bucket) {
    if (entry.word_ == word) {
      return entry.count_;
    }
  }

  return 0;
}
