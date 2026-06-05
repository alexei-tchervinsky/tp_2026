#include "dict.hpp"
#include "utils.hpp"
#include <iostream>
#include <algorithm>
#include <stdexcept>

HashTable::HashTable(std::size_t initial_size) : table_(initial_size)
{
    if (initial_size == 0)
    {
        throw std::invalid_argument("HashTable: initial_size cannot be 0");
    }
}

bool HashTable::insert(const std::string &key, const std::string &translation)
{
    std::string lowerKey = toLower(key);
    if (lowerKey.empty())
    {
        throw std::invalid_argument("insert: key cannot be empty");
    }
    if (translation.empty())
    {
        throw std::invalid_argument("insert: translation cannot be empty");
    }

    auto &vec = table_[lowerKey].translations_;

    if (std::find(vec.begin(), vec.end(), translation) == vec.end())
    {
        vec.push_back(translation);
        std::sort(vec.begin(), vec.end());
    }
    return true;
}

bool HashTable::remove(const std::string &key)
{
    if (key.empty())
    {
        throw std::invalid_argument("remove: key cannot be empty");
    }
    return table_.erase(toLower(key)) > 0;
}

HashTable::KeyValue *HashTable::find(const std::string &key)
{
    if (key.empty())
    {
        throw std::invalid_argument("find: key cannot be empty");
    }
    auto it = table_.find(toLower(key));
    if (it == table_.end())
    {
        return nullptr;
    }
    return &(it->second);
}

void HashTable::print() const
{
    std::cout << "\n======= ХЕШ-ТАБЛИЦА (STL) =======\n";
    for (std::size_t i = 0; i < table_.bucket_count(); ++i)
    {
        std::cout << i << " ";
        if (table_.bucket_size(i) == 0)
        {
            std::cout << "empty\n";
        }
        else
        {
            for (auto local_it = table_.begin(i); local_it != table_.end(i); ++local_it)
            {
                std::cout << local_it->first << ": ";
                for (const auto &t : local_it->second.translations_)
                {
                    std::cout << t << " ";
                }
                std::cout << "| ";
            }
            std::cout << "\n";
        }
    }
    std::cout << "\n=================================\n";
}

int HashTable::get_collisions() const
{
    int collision_count = 0;
    for (std::size_t i = 0; i < table_.bucket_count(); ++i)
    {
        std::size_t b_size = table_.bucket_size(i);
        if (b_size > 1)
        {
            collision_count += static_cast<int>(b_size - 1);
        }
    }
    return collision_count;
}
