#include "freq_dict.hpp"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <utility>
#include <cctype>
#include <stdexcept>

FreqDict::FreqDict(int size)
    : table_((size > 0) ? size : DEFAULT_SIZE),
      size_((size > 0) ? size : DEFAULT_SIZE),
      number_(0),
      collisionCount_(0)
{
    if (size <= 0) {
        throw std::invalid_argument("FreqDict: size must be positive");
    }
}

FreqDict::FreqDict(const FreqDict& other)
    : table_(other.size_),
      size_(other.size_),
      number_(other.number_),
      collisionCount_(other.collisionCount_)
{
    for (int i = 0; i < size_; ++i) {
        table_[i] = other.table_[i];
    }
}

FreqDict::FreqDict(FreqDict&& other) noexcept
    : table_(std::move(other.table_)),
      size_(other.size_),
      number_(other.number_),
      collisionCount_(other.collisionCount_)
{
    other.size_ = 0;
    other.number_ = 0;
    other.collisionCount_ = 0;
}

FreqDict& FreqDict::operator=(FreqDict other) noexcept
{
    swap(*this, other);
    return *this;
}

void swap(FreqDict& first, FreqDict& second) noexcept
{
    using std::swap;
    swap(first.table_, second.table_);
    swap(first.size_, second.size_);
    swap(first.number_, second.number_);
    swap(first.collisionCount_, second.collisionCount_);
}

std::string FreqDict::normalize(const std::string& word)
{
    std::string result;
    result.reserve(word.size());
    for (unsigned char ch : word) {
        result += static_cast<char>(std::tolower(ch));
    }
    return result;
}

std::size_t FreqDict::hashFunction(const std::string& key) const
{
    std::size_t hash = 0;
    for (unsigned char ch : key) {
        hash = hash * 31 + ch;
    }
    return hash % static_cast<std::size_t>(size_);
}

void FreqDict::insert(const std::string& word)
{
    if (word.empty()) {
        throw std::invalid_argument("FreqDict::insert: empty word");
    }

    const std::string key = normalize(word);
    std::size_t index = hashFunction(key);

    for (auto& node : table_[index]) {
        if (node.key == key) {
            node.count++;
            return;
        }
    }

    if (!table_[index].empty()) {
        collisionCount_++;
    }

    table_[index].push_back(Node(key, 1));
    number_++;
}

int FreqDict::search(const std::string& word) const
{
    if (word.empty()) {
        return 0;
    }

    const std::string key = normalize(word);
    std::size_t index = hashFunction(key);

    for (const auto& node : table_[index]) {
        if (node.key == key) {
            return node.count;
        }
    }
    return 0;
}

bool FreqDict::remove(const std::string& word)
{
    if (word.empty()) {
        return false;
    }

    const std::string key = normalize(word);
    std::size_t index = hashFunction(key);

    for (auto it = table_[index].begin(); it != table_[index].end(); ++it) {
        if (it->key == key) {
            table_[index].erase(it);
            number_--;
            return true;
        }
    }
    return false;
}

std::vector<std::pair<std::string, int>> FreqDict::getAllWords() const
{
    std::vector<std::pair<std::string, int>> result;
    for (const auto& bucket : table_) {
        for (const auto& node : bucket) {
            result.push_back({node.key, node.count});
        }
    }
    return result;
}

std::vector<std::pair<std::string, int>> FreqDict::getTop3() const
{
    auto allWords = getAllWords();
    if (allWords.empty()) {
        return {};
    }

    std::sort(allWords.begin(), allWords.end(),
              [](const auto& a, const auto& b) {
                  return a.second > b.second;
              });

    int topCount = std::min(3, static_cast<int>(allWords.size()));
    return std::vector<std::pair<std::string, int>>(
        allWords.begin(), allWords.begin() + topCount);
}

void FreqDict::print() const
{
    std::cout << "\n=== Hash Table (chaining) ===\n";
    std::cout << "Size: " << size_
              << ", used: " << number_
              << ", load: " << std::fixed << std::setprecision(2) << loadFactor()
              << ", collisions: " << collisionCount_ << "\n\n";

    std::cout << std::left
              << std::setw(8) << "Index"
              << std::setw(30) << "List (key:count)"
              << "\n" << std::string(45, '-') << "\n";

    for (int i = 0; i < size_; ++i) {
        std::cout << std::setw(8) << i;
        if (table_[i].empty()) {
            std::cout << "-> NULL\n";
        } else {
            bool first = true;
            for (const auto& node : table_[i]) {
                if (!first) std::cout << std::setw(8) << "";
                std::cout << "-> [" << node.key << ":" << node.count << "] ";
                first = false;
            }
            std::cout << "-> NULL\n";
        }
    }
    std::cout << std::endl;
}

