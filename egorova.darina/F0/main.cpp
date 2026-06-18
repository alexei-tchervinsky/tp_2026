#include <iostream>
#include <string>
#include <vector>
#include "Dictionary.hpp"

/**
 * Вспомогательная функция для красивого вывода результатов поиска
 */
void printSearchResult(const Dictionary& dict, const std::string& word) {
    std::cout << "Searching for '" << word << "': ";

    const TranslationList* list = dict.search(word);

    if (list) {
        const auto& translations = list->getTranslations();
        std::cout << "Found " << translations.size() << " translation(s): ";
        for (const auto& tr : translations) {
            std::cout << "[" << tr << "] ";
        }
        std::cout << std::endl;
    } else {
        std::cout << "NOT FOUND. The word '" << word
                  << "' is missing from the dictionary." << std::endl;
    }
}

// Вспомогательная функция для проверки наличия слова
void checkWord(const Dictionary& dict, const std::string& word) {
    const TranslationList* list = dict.search(word);
    std::cout << "Word '" << word << "': "
              << (list ? "Present" : "Absent") << std::endl;
}

int main() {
    Dictionary dictionary;

    std::cout << "--- English-Russian Dictionary (2-3 Tree) ---\n" << std::endl;

    try {
        dictionary.insert("apple", "яблоко");
        dictionary.insert("book", "книга");
        dictionary.insert("book", "резервировать");
        dictionary.insert("ocean", "океан");

        printSearchResult(dictionary, "book");
        printSearchResult(dictionary, "apple");

        std::cout << "---------------------------------------------" << std::endl;

        printSearchResult(dictionary, "laptop");
        printSearchResult(dictionary, "sky");

        std::cout << "---------------------------------------------" << std::endl;

        std::cout << "Action: Removing existing word 'ocean'..." << std::endl;
        dictionary.remove("ocean");
        checkWord(dictionary, "ocean");
        checkWord(dictionary, "apple");

        std::cout << "---------------------------------------------" << std::endl;

        std::cout << "Action: Attempting to remove non-existent word 'banana'..."
                  << std::endl;

        dictionary.remove("banana");

        std::cout << "Result: System stable." << std::endl;
        checkWord(dictionary, "apple");
        std::cout << "---------------------------------------------" << std::endl;

        std::cout << "Action: Testing removal with empty key:" << std::endl;
        dictionary.remove("");
        std::cout << "Result: System ignored empty key safely." << std::endl;

        std::cout << "---------------------------------------------" << std::endl;

        std::cout << "Testing exception handling for empty key:" << std::endl;
        dictionary.insert("", "некорректные данные");

    } catch (const std::exception& e) {
        std::cout << "SYSTEM LOG: " << e.what() << std::endl;
    }
    return 0;
}
