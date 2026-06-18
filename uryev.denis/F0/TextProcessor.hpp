#ifndef TEXT_PROCESSOR_HPP
#define TEXT_PROCESSOR_HPP

#include <string>
#include <unordered_map>

class TextProcessor {
private:
  std::string cleanWord(const std::string& raw_word) const;

public:
  bool processFile(const std::string& filename, std::unordered_map<std::string, int>& table);
};

#endif
