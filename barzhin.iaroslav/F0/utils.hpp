#ifndef UTILS_HPP
#define UTILS_HPP

#include <algorithm>
#include <string>
#include <cctype>
#include <vector>

#include "WordEntry.hpp"

std::string cleanWord(const std::string& word);
std::string getInputFilePath(const char* executablePath, int argc, char* argv[]);
void fillVector(std::vector<WordEntry> &out, const std::vector<WordEntry> &bucket);

#endif // UTILS_HPP
