#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP

#include <string>
#include <unordered_map>

class HashTable
{
public:
    HashTable() = default;
    ~HashTable() = default;

    HashTable(const HashTable&) = delete;
    HashTable& operator=(const HashTable&) = delete;
    HashTable(HashTable&&) = default;
    HashTable& operator=(HashTable&&) = default;

    void insert(const std::string& word);
    int search(const std::string& word) const;
    void remove(const std::string& word);

    void printTop3() const;
    void printTable() const;

private:
    std::unordered_map<std::string, int> table_;

    void validateKey_(const std::string& word) const;
};

#endif // HASHTABLE_HPP
