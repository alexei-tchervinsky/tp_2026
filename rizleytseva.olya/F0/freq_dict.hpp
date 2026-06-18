#ifndef FREQ_DICT_HPP
#define FREQ_DICT_HPP

#include <string>
#include <vector>
#include <list>
#include <utility>

// Частотный словарь на основе хеш-таблицы с методом цепочек.
// Все ключи хранятся в нижнем регистре (нормализация в insert/search/remove).
class FreqDict {
public:
    // Конструкторы / деструктор
    explicit FreqDict(int size = DEFAULT_SIZE);            // список инициализации
    FreqDict(const FreqDict& other);                       // копирующий конструктор
    FreqDict(FreqDict&& other) noexcept;                   // перемещающий конструктор
    ~FreqDict() = default;                                 // деструктор (автоматический)

    // Операторы присваивания
    FreqDict& operator=(FreqDict other) noexcept;          // copy-and-swap (и копирующий, и перемещающий)

    // Дружественная функция swap (для copy-and-swap)
    friend void swap(FreqDict& first, FreqDict& second) noexcept;

    // Основные операции словаря
    void insert(const std::string& word);                  // INSERT (слово приводится к нижнему регистру)
    int  search(const std::string& word) const;            // SEARCH (регистронезависимый)
    bool remove(const std::string& word);                  // DELETE (регистронезависимый)

    // Дополнительные методы для частотного словаря
    std::vector<std::pair<std::string, int>> getAllWords() const;
    std::vector<std::pair<std::string, int>> getTop3() const;

    // Геттеры (тривиальные – в теле класса)
    int    getSize()           const { return size_; }
    int    getNumber()         const { return number_; }
    int    getCollisionCount() const { return collisionCount_; }
    double loadFactor()        const { return static_cast<double>(number_) / size_; }
    void   print()             const;

    // Хеш-функция (принимает строку в нижнем регистре)
    std::size_t hashFunction(const std::string& key) const;

private:
    static const int DEFAULT_SIZE = 101;

    // Узел для списка в ячейке таблицы
    struct Node {
        std::string key;
        int count;

        // Список инициализации в конструкторе
        Node(const std::string& k, int c = 1) : key(k), count(c) {}
    };

    //Вспомогательный метод нормализации ключа
    static std::string normalize(const std::string& word);

    std::vector<std::list<Node>> table_;  // метод цепочек
    int size_;                            // размер таблицы
    int number_;                          // количество уникальных слов
    int collisionCount_;                  // счётчик коллизий (не mutable: изменяется только в insert)
};

#endif 
