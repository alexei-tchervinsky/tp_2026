#include "freq_dict.hpp"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <utility>
#include <cctype>
#include <stdexcept>

// Конструкторы и деструктор

// Конструктор с параметром (список инициализации)
// FIX: добавлена валидация size > 0
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

// Копирующий конструктор (глубокое копирование списков)
FreqDict::FreqDict(const FreqDict& other)
    : table_(other.size_),
      size_(other.size_),
      number_(other.number_),
      collisionCount_(other.collisionCount_)
{
    // std::list::operator= делает глубокое копирование
    for (int i = 0; i < size_; ++i) {
        table_[i] = other.table_[i];
    }
}

// Перемещающий конструктор
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

// Оператор присваивания (copy-and-swap)
FreqDict& FreqDict::operator=(FreqDict other) noexcept
{
    swap(*this, other);
    return *this;
}

// Реализация swap для идиомы copy-and-swap
void swap(FreqDict& first, FreqDict& second) noexcept
{
    using std::swap;
    swap(first.table_, second.table_);
    swap(first.size_, second.size_);
    swap(first.number_, second.number_);
    swap(first.collisionCount_, second.collisionCount_);
}

// Нормализация ключа
// FIX: вынесено в отдельный метод, используется в insert/search/remove
std::string FreqDict::normalize(const std::string& word)
{
    std::string result;
    result.reserve(word.size());
    for (unsigned char ch : word) {
        result += static_cast<char>(std::tolower(ch));
    }
    return result;
}

// Хеш-функция
std::size_t FreqDict::hashFunction(const std::string& key) const
{
    std::size_t hash = 0;
    for (unsigned char ch : key) {
        hash = hash * 31 + ch;
    }
    return hash % static_cast<std::size_t>(size_);
}

// INSERT
void FreqDict::insert(const std::string& word)
{
    if (word.empty()) {
        throw std::invalid_argument("FreqDict::insert: empty word");
    }

    // FIX: нормализуем ключ перед хешированием (регистронезависимость)
    const std::string key = normalize(word);
    std::size_t index = hashFunction(key);

    for (auto& node : table_[index]) {
        if (node.key == key) {
            node.count++;
            return;
        }
    }

    // FIX: коллизия фиксируется один раз при добавлении нового слова в занятый bucket,
    //      а не при каждом сравнении в цикле
    if (!table_[index].empty()) {
        collisionCount_++;
    }

    table_[index].push_back(Node(key, 1));
    number_++;
}

// SEARCH
int FreqDict::search(const std::string& word) const
{
    if (word.empty()) {
        return 0;
    }

    // FIX: нормализуем ключ для регистронезависимого поиска
    const std::string key = normalize(word);
    std::size_t index = hashFunction(key);

    for (const auto& node : table_[index]) {
        if (node.key == key) {
            return node.count;
        }
    }
    return 0;
}

// DELETE
bool FreqDict::remove(const std::string& word)
{
    if (word.empty()) {
        return false;
    }

    // FIX: нормализуем ключ для регистронезависимого удаления
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

// Получить все пары (слово, частота)
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

// Три самых частых слова
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

// Печать таблицы
void FreqDict::print() const
{
    std::cout << "\n=== Хеш-таблица (метод цепочек) ===\n";
    std::cout << "Размер: " << size_
              << ", занято: " << number_
              << ", загрузка: " << std::fixed << std::setprecision(2) << loadFactor()
              << ", коллизий: " << collisionCount_ << "\n\n";

    std::cout << std::left
              << std::setw(8) << "Индекс"
              << std::setw(30) << "Список (ключ:частота)"
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
