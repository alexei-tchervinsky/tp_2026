#ifndef DICT_HPP
#define DICT_HPP

#include <string>
#include <vector>
#include <unordered_map>

class HashTable
{
public:
    struct KeyValue
    {
        std::vector<std::string> translations_;
    };

private:
    std::unordered_map<std::string, KeyValue> table_;

public:
    HashTable(const HashTable &) = delete;
    HashTable &operator=(const HashTable &) = delete;
    HashTable(HashTable &&) = delete;
    HashTable &operator=(HashTable &&) = delete;

    HashTable(std::size_t initial_size = 41);
    ~HashTable() = default;

    bool insert(const std::string &key, const std::string &translation);
    bool remove(const std::string &key);
    KeyValue *find(const std::string &key);
    void print() const;

    std::size_t get_number() const { return table_.size(); }
    int get_collisions() const;
};

#endif
