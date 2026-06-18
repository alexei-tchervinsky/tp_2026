#include "HashTable.hpp"

#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <vector>

void HashTable::validateKey_(const std::string& word) const
{
    if (word.empty())
        throw std::invalid_argument("Key must not be empty.");
}

void HashTable::insert(const std::string& word)
{
    validateKey_(word);
    ++table_[word];
}

int HashTable::search(const std::string& word) const
{
    validateKey_(word);

    auto it = table_.find(word);
    return (it != table_.end()) ? it->second : 0;
}

void HashTable::remove(const std::string& word)
{
    validateKey_(word);

    auto it = table_.find(word);
    if (it == table_.end())
        throw std::runtime_error("Remove failed: word not found in table.");

    table_.erase(it);
}

void HashTable::printTop3() const
{
    if (table_.empty())
    {
        std::cout << "\n- Top-3 most frequent words -\n  (table is empty)\n";
        return;
    }

    std::vector<std::pair<int, std::string>> entries;
    entries.reserve(table_.size());

    for (const auto& kv : table_)
        entries.emplace_back(kv.second, kv.first);

    const std::size_t topN = std::min<std::size_t>(3, entries.size());
    std::partial_sort(entries.begin(),
        entries.begin() + static_cast<std::ptrdiff_t>(topN),
        entries.end(),
        [](const std::pair<int, std::string>& a,
            const std::pair<int, std::string>& b) {
                return a.first > b.first;
        });

    std::cout << "\n- Top-3 most frequent words -\n";
    for (std::size_t i = 0; i < topN; ++i)
    {
        std::cout << "  " << (i + 1) << ". \""
            << entries[i].second << "\"  --  "
            << entries[i].first << " time(s)\n";
    }
}

void HashTable::printTable() const
{
    std::cout << "\n- Hash table -\n";
    for (const auto& kv : table_)
        std::cout << "  \"" << kv.first << "\": " << kv.second << "\n";
}
