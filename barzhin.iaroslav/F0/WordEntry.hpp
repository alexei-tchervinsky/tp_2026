#ifndef WORD_ENTRY_HPP
#define WORD_ENTRY_HPP

#include <string>

struct WordEntry {
  std::string word_;
  int count_;

  bool operator<(const WordEntry& other) const { return word_ < other.word_; }
  bool operator==(const WordEntry& other) const { return word_ == other.word_; }
  bool operator>(const WordEntry& other) const { return word_ > other.word_; }
};

#endif // WORD_ENTRY_HPP
