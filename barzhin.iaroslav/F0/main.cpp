#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "HashTable.hpp"
#include "utils.hpp"

int main(int argc, char* argv[]) {
  const std::string inputFilePath = getInputFilePath(argv[0], argc, argv);
  std::ifstream file(inputFilePath);
  if (!file.is_open()) {
    std::cerr << "Unable to open file." << std::endl;
    return 1;
  }

  HashTable hashTable(1001);
  std::string word;

  while (file >> word) {
    std::string clean = cleanWord(word);
    if (!clean.empty()) {
      hashTable.addWord(clean);
    }
  }

  std::vector<WordEntry> words;
  for (std::size_t i = 0; i < hashTable.getSize(); ++i) {
    fillVector(words, hashTable.getBucket(i));
  }

  std::sort(words.begin(), words.end(),
    [](const WordEntry& lhs, const WordEntry& rhs) {
      return lhs.count_ > rhs.count_;
    });

  std::cout << "--- Top 3 Words ---" << std::endl;
  for (int i = 0; i < std::min(3, static_cast<int>(words.size()));
       ++i) {
    std::cout << i + 1 << ". " << words[i].word_ << ": "
              << words[i].count_ << std::endl;
  }

  return 0;
}
