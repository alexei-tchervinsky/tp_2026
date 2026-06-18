#ifndef FREQ_DICT_HPP
#define FREQ_DICT_HPP

#include <string>
#include <vector>
#include <list>
#include <utility>

class FreqDict {
public:
    explicit FreqDict(int size = DEFAULT_SIZE);
    FreqDict(const FreqDict& other);
    FreqDict(FreqDict&& other) noexcept;
    ~FreqDict() = default;

    FreqDict& operator=(FreqDict other) noexcept;

    friend void swap(FreqDict& first, FreqDict& second) noexcept;

    void insert(const std::string& word);
    int  search(const std::string& word) const;
    bool remove(const std::string& word);

    std::vector<std::pair<std::string, int>> getAllWords() const;
    std::vector<std::pair<std::string, int>> getTop3() const;

    int    getSize()           const { return size_; }
    int    getNumber()         const { return number_; }
    int    getCollisionCount() const { return collisionCount_; }
    double loadFactor()        const { return static_cast<double>(number_) / size_; }
    void   print()             const;

    std::size_t hashFunction(const std::string& key) const;

private:
    static const int DEFAULT_SIZE = 101;

    struct Node {
        std::string key;
        int count;
        Node(const std::string& k, int c = 1) : key(k), count(c) {}
    };

    static std::string normalize(const std::string& word);

    std::vector<std::list<Node>> table_;
    int size_;
    int number_;
    int collisionCount_;
};

#endif

