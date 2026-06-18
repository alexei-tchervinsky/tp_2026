#include "Analytics.hpp"
#include <iostream>
#include <vector>
#include <algorithm>

void Analytics::printTop3(const std::unordered_map<std::string, int> &table) const
{
  std::vector<std::pair<std::string, int>> all_words;
  for (const auto &pair : table)
  {
    all_words.push_back(pair);
  }
  if (all_words.empty())
  {
    std::cout << "\n Текст не содержит слов для анализа.\n";
    return;
  }
  std::sort(all_words.begin(), all_words.end(), [](const auto &a, const auto &b)
            { return a.second > b.second; });
  std::cout << "\n=========== ТОП-3 САМЫХ ЧАСТЫХ СЛОВ ==========" << std::endl;
  std::size_t limit = std::min(all_words.size(), static_cast<std::size_t>(3));
  for (std::size_t i = 0; i < limit; ++i)
  {
    std::cout << i + 1 << ". Слово: \"" << all_words[i].first
              << "\" встретилось " << all_words[i].second << " раз(а)." << std::endl;
  }
  std::cout << "================================================" << std::endl;
}
