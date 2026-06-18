#include "freq_dict.hpp"
#include <iostream>
#include <fstream>
#include <cctype>
#include <vector>
#include <stdexcept>

// ------------------------------------------------------------
// Вспомогательные функции обработки текста
// Нормализация регистра уже выполняется внутри FreqDict,
// но extractWords всё равно приводит к нижнему регистру —
// это не навредит и делает намерение явным.
// ------------------------------------------------------------
bool isLetter(char ch) {
    return std::isalpha(static_cast<unsigned char>(ch));
}

std::string toLower(const std::string& str) {
    std::string result = str;
    for (char& ch : result) {
        ch = static_cast<char>(std::tolower(static_cast<unsigned char>(ch)));
    }
    return result;
}

std::vector<std::string> extractWords(const std::string& line) {
    std::vector<std::string> words;
    std::string currentWord;
    for (char ch : line) {
        if (isLetter(ch)) {
            currentWord += ch;
        } else {
            if (!currentWord.empty()) {
                words.push_back(toLower(currentWord));
                currentWord.clear();
            }
        }
    }
    if (!currentWord.empty()) {
        words.push_back(toLower(currentWord));
    }
    return words;
}

// ------------------------------------------------------------
// Тестовые вспомогательные функции
// ------------------------------------------------------------
static void testInsert(FreqDict& dict, const std::string& word) {
    try {
        dict.insert(word);
        std::cout << "[INSERT] \"" << word << "\" -> OK\n";
    } catch (const std::exception& e) {
        std::cout << "[INSERT] \"" << word << "\" -> ОШИБКА: " << e.what() << "\n";
    }
}

static void testSearch(const FreqDict& dict, const std::string& word) {
    int count = dict.search(word);
    if (count > 0)
        std::cout << "[SEARCH] \"" << word << "\" -> " << count << " раз(а)\n";
    else
        std::cout << "[SEARCH] \"" << word << "\" -> НЕ НАЙДЕН\n";
}

static void testRemove(FreqDict& dict, const std::string& word) {
    bool ok = dict.remove(word);
    std::cout << "[DELETE] \"" << word << "\" : " << (ok ? "OK" : "НЕ НАЙДЕН") << "\n";
}

// ------------------------------------------------------------
// main
// ------------------------------------------------------------
int main() {
    std::cout << "==============================================\n";
    std::cout << "  ЧАСТОТНЫЙ СЛОВАРЬ (хеш-таблица + цепочки)\n";
    std::cout << "==============================================\n\n";

    // --- ТЕСТ 1: INSERT, SEARCH, DELETE ---
    std::cout << "=== ТЕСТ 1: INSERT, SEARCH, DELETE ===\n";
    FreqDict dict(11);
    testInsert(dict, "cat");
    testInsert(dict, "dog");
    testInsert(dict, "cat");
    testInsert(dict, "bird");
    testInsert(dict, "cat");
    testInsert(dict, "");           // пустое слово — исключение
    dict.print();

    testSearch(dict, "cat");
    testSearch(dict, "dog");
    testSearch(dict, "fish");       // отсутствующее слово

    testRemove(dict, "cat");
    testRemove(dict, "cat");        // повторное удаление — не найдено
    testSearch(dict, "cat");
    dict.print();

    // --- ТЕСТ 2: Топ-3 самых частых ---
    std::cout << "\n=== ТЕСТ 2: Топ-3 самых частых ===\n";
    FreqDict dict2(11);
    std::vector<std::string> words = {"the", "the", "the", "the",
                                      "cat", "cat", "cat",
                                      "dog", "dog",
                                      "bird"};
    for (const auto& w : words) dict2.insert(w);
    auto top3 = dict2.getTop3();
    for (size_t i = 0; i < top3.size(); ++i) {
        std::cout << "  " << i + 1 << ". \""
                  << top3[i].first << "\" — " << top3[i].second << "\n";
    }

    // --- ТЕСТ 3: Чтение из файла input.txt ---
    std::cout << "\n=== ТЕСТ 3: Чтение из файла input.txt ===\n";
    std::ifstream file("input.txt");
    if (!file.is_open()) {
        std::cout << "Файл input.txt не найден, тест пропущен.\n";
    } else {
        FreqDict fileDict(101);
        std::string line;
        while (std::getline(file, line)) {
            auto fileWords = extractWords(line);
            for (const auto& w : fileWords) fileDict.insert(w);
        }
        file.close();
        fileDict.print();
        auto fileTop = fileDict.getTop3();
        std::cout << "\nТри самых частых слова в файле:\n";
        for (size_t i = 0; i < fileTop.size(); ++i) {
            std::cout << "  " << i + 1 << ". \""
                      << fileTop[i].first << "\" — " << fileTop[i].second << "\n";
        }
    }

    // --- ТЕСТ 4: Регистронезависимость ---
    // FIX: теперь insert нормализует ключ внутри себя,
    //      поэтому "Hello", "HELLO", "hello" → одна запись с частотой 3
    std::cout << "\n=== ТЕСТ 4: Регистронезависимость ===\n";
    FreqDict caseDict(11);
    caseDict.insert("Hello");
    caseDict.insert("HELLO");
    caseDict.insert("hello");
    testSearch(caseDict, "hello");  // ожидается 3

    // --- ТЕСТ 5: Статистика коллизий ---
    // FIX: коллизия считается один раз при добавлении нового ключа в занятый bucket
    std::cout << "\n=== ТЕСТ 5: Статистика коллизий ===\n";
    FreqDict colDict(7);
    testInsert(colDict, "a");
    testInsert(colDict, "b");
    testInsert(colDict, "c");
    testInsert(colDict, "d");
    testInsert(colDict, "e");
    testInsert(colDict, "f");
    std::cout << "Всего коллизий: " << colDict.getCollisionCount() << "\n";
    colDict.print();

    // --- ТЕСТ 6: Конструкторы и операторы копирования/перемещения ---
    std::cout << "\n=== ТЕСТ 6: Конструкторы и операторы копирования/перемещения ===\n";
    FreqDict original(11);
    original.insert("test");
    original.insert("copy");
    original.insert("test");
    std::cout << "Оригинал: уникальных слов = " << original.getNumber() << "\n";

    // Конструктор копирования
    FreqDict copied(original);
    std::cout << "Копия:    уникальных слов = " << copied.getNumber() << "\n";
    std::cout << "Копия: частота 'test' = " << copied.search("test")
              << " (ожидается 2)\n";

    // Оператор присваивания (copy-and-swap)
    FreqDict assigned(5);
    assigned = original;
    std::cout << "Присвоенный: уникальных слов = " << assigned.getNumber() << "\n";
    std::cout << "Присвоенный: частота 'copy' = " << assigned.search("copy")
              << " (ожидается 1)\n";

    // Конструктор перемещения
    FreqDict moved(std::move(original));
    std::cout << "После перемещения: оригинал->уникальных слов = "
              << original.getNumber() << " (ожидается 0)\n";
    std::cout << "Перемещённый: уникальных слов = "
              << moved.getNumber() << " (ожидается 2)\n";

    // Оператор перемещающего присваивания (через тот же operator=)
    FreqDict moveAssigned(3);
    moveAssigned = std::move(moved);
    std::cout << "После перемещающего присваивания: moved->уникальных слов = "
              << moved.getNumber() << " (ожидается 0)\n";
    std::cout << "moveAssigned: уникальных слов = "
              << moveAssigned.getNumber() << " (ожидается 2)\n";

    // --- ТЕСТ 7: Некорректный размер таблицы ---
    std::cout << "\n=== ТЕСТ 7: Некорректный размер (size <= 0) ===\n";
    try {
        FreqDict badDict(-5);
        std::cout << "Ошибка: исключение не было выброшено!\n";
    } catch (const std::invalid_argument& e) {
        std::cout << "Поймано исключение: " << e.what() << " -> OK\n";
    }

    std::cout << "\n==============================================\n";
    std::cout << "  ВСЕ ТЕСТЫ ЗАВЕРШЕНЫ\n";
    std::cout << "==============================================\n";

    return 0;
}
