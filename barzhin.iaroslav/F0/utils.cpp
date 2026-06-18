#include "utils.hpp"

std::string cleanWord(const std::string& word) {
  std::string result;
  for (const unsigned char c : word) {
    if (std::isalpha(c)) {
      result += std::tolower(c);
    }
  }
  return result;
}

std::string getInputFilePath(const char* executablePath, int argc, char* argv[]) {
  if (argc > 1) {
    return argv[1];
  }

  std::string path = executablePath != nullptr ? executablePath : "";
  const std::size_t slashPos = path.find_last_of('/');
  if (slashPos == std::string::npos) {
    return "text.txt";
  }

  return path.substr(0, slashPos + 1) + "text.txt";
}

void fillVector(std::vector<WordEntry> &out, const std::vector<WordEntry> &bucket) {
  for (const auto& entry : bucket) {
    out.push_back(entry);
  }
}
