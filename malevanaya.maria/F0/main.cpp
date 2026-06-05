#include "HashTable.hpp"
#include "TextProcessor.hpp"

#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>

#ifdef _WIN32
#include <windows.h>
#endif

static void runTests()
{
    std::cout << "-TESTS-\n";

    // 1. Valid input: insert / search / remove.
    std::cout << "\n[1. Valid input - INSERT / SEARCH / REMOVE]\n";
    {
        auto ht = std::make_unique<HashTable>();

        ht->insert("apple");
        ht->insert("banana");
        ht->insert("apple");
        ht->insert("apple");
        ht->insert("cherry");
        ht->insert("banana");

        std::cout << "SEARCH \"apple\"  (inserted 3x) -> returns: " << ht->search("apple") << "\n";
        std::cout << "SEARCH \"banana\" (inserted 2x) -> returns: " << ht->search("banana") << "\n";
        std::cout << "SEARCH \"cherry\" (inserted 1x) -> returns: " << ht->search("cherry") << "\n";
        std::cout << "SEARCH \"mango\"  (absent)       -> returns: " << ht->search("mango") << "\n";

        ht->remove("cherry");
        std::cout << "After REMOVE \"cherry\", SEARCH \"cherry\" -> returns: "
            << ht->search("cherry") << "\n";

        ht->remove("apple");
        std::cout << "After REMOVE \"apple\",  SEARCH \"apple\"  -> returns: "
            << ht->search("apple") << "\n";
    }

    // 2. Invalid input: empty / blank / digits / punctuation.
    std::cout << "\n[2. Invalid input - empty / blank / digits / punctuation]\n";
    {
        auto ht = std::make_unique<HashTable>();
        ht->insert("word");

        // Empty string "".
        try {
            ht->insert("");
            std::cout << "INSERT \"\" -> (No exception thrown)\n";
        }
        catch (const std::exception& e) {
            std::cout << "INSERT \"\" -> Exception caught: " << e.what() << "\n";
        }

        try {
            ht->search("");
            std::cout << "SEARCH \"\" -> returned: " << ht->search("") << "\n";
        }
        catch (const std::exception& e) {
            std::cout << "SEARCH \"\" -> Exception caught: " << e.what() << "\n";
        }

        try {
            ht->remove("");
            std::cout << "REMOVE \"\" -> (No exception thrown)\n";
        }
        catch (const std::exception& e) {
            std::cout << "REMOVE \"\" -> Exception caught: " << e.what() << "\n";
        }

        // Whitespace-only "   ".
        try {
            ht->insert("   ");
            std::cout << "INSERT \"   \" -> (No exception thrown)\n";
        }
        catch (const std::exception& e) {
            std::cout << "INSERT \"   \" -> Exception caught: " << e.what() << "\n";
        }

        try {
            ht->search("   ");
            std::cout << "SEARCH \"   \" -> returned: " << ht->search("   ") << "\n";
        }
        catch (const std::exception& e) {
            std::cout << "SEARCH \"   \" -> Exception caught: " << e.what() << "\n";
        }

        try {
            ht->remove("   ");
            std::cout << "REMOVE \"   \" -> (No exception thrown)\n";
        }
        catch (const std::exception& e) {
            std::cout << "REMOVE \"   \" -> Exception caught: " << e.what() << "\n";
        }

        // Digits-only "12345".
        try {
            ht->insert("12345");
            std::cout << "INSERT \"12345\" -> (No exception thrown)\n";
        }
        catch (const std::exception& e) {
            std::cout << "INSERT \"12345\" -> Exception caught: " << e.what() << "\n";
        }

        try {
            ht->search("12345");
            std::cout << "SEARCH \"12345\" -> returned: " << ht->search("12345") << "\n";
        }
        catch (const std::exception& e) {
            std::cout << "SEARCH \"12345\" -> Exception caught: " << e.what() << "\n";
        }

        try {
            ht->remove("12345");
            std::cout << "REMOVE \"12345\" -> (No exception thrown)\n";
        }
        catch (const std::exception& e) {
            std::cout << "REMOVE \"12345\" -> Exception caught: " << e.what() << "\n";
        }

        // Punctuation-only "!?..".
        try {
            ht->insert("!?..");
            std::cout << "INSERT \"!?..\" -> (No exception thrown)\n";
        }
        catch (const std::exception& e) {
            std::cout << "INSERT \"!?..\" -> Exception caught: " << e.what() << "\n";
        }

        try {
            ht->search("!?..");
            std::cout << "SEARCH \"!?..\" -> returned: " << ht->search("!?..") << "\n";
        }
        catch (const std::exception& e) {
            std::cout << "SEARCH \"!?..\" -> Exception caught: " << e.what() << "\n";
        }

        try {
            ht->remove("!?..");
            std::cout << "REMOVE \"!?..\" -> (No exception thrown)\n";
        }
        catch (const std::exception& e) {
            std::cout << "REMOVE \"!?..\" -> Exception caught: " << e.what() << "\n";
        }
    }

    // 3. Invalid input: remove absent / already removed.
    std::cout << "\n[3. Invalid input - REMOVE absent / already removed]\n";
    {
        auto ht = std::make_unique<HashTable>();
        ht->insert("hello");

        try {
            ht->remove("nothere");
            std::cout << "REMOVE absent word \"nothere\" -> (No exception thrown)\n";
        }
        catch (const std::exception& e) {
            std::cout << "REMOVE absent word \"nothere\" -> Exception caught: " << e.what() << "\n";
        }

        ht->remove("hello");
        try {
            ht->remove("hello");
            std::cout << "REMOVE already removed \"hello\" -> (No exception thrown)\n";
        }
        catch (const std::exception& e) {
            std::cout << "REMOVE already removed \"hello\" -> Exception caught: " << e.what() << "\n";
        }
    }

    // 4. Invalid input: file operations.
    std::cout << "\n[4. Invalid input - file operations]\n";
    {
        auto ht = std::make_unique<HashTable>();

        try
        {
            TextProcessor::processFile("__no_such_file__.txt", *ht);
            std::cout << "processFile non-existent -> (No exception thrown)\n";
        }
        catch (const std::exception& e)
        {
            std::cout << "processFile non-existent -> Exception caught: " << e.what() << "\n";
        }

        try
        {
            TextProcessor::processFile("", *ht);
            std::cout << "processFile empty path -> (No exception thrown)\n";
        }
        catch (const std::exception& e)
        {
            std::cout << "processFile empty path -> Exception caught: " << e.what() << "\n";
        }
    }

    // 5. Edge cases.
    std::cout << "\n[5. Edge cases]\n";
    {
        auto ht = std::make_unique<HashTable>();

        ht->insert("a");
        std::cout << "INSERT single char \"a\" -> count: " << ht->search("a") << "\n";

        std::string longWord(200, 'z');
        ht->insert(longWord);
        std::cout << "INSERT 200-char word -> count: " << ht->search(longWord) << "\n";

        for (int i = 0; i < 1000; ++i)
            ht->insert("stress");
        std::cout << "INSERT \"stress\" x1000 -> count: " << ht->search("stress") << "\n";

        // Re-insert after remove.
        ht->insert("temp");
        ht->remove("temp");
        ht->insert("temp");
        std::cout << "INSERT after REMOVE -> count: " << ht->search("temp") << "\n";
    }
}


int main()
{
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif

    runTests();

    std::cout << "\n--FREQUENCY DICTIONARY--\n";

    HashTable         ht;
    const std::string filePath = "text.txt";

    try
    {
        int total = TextProcessor::processFile(filePath, ht);
        std::cout << "File: " << filePath << "\n";
        std::cout << "Words read: " << total << "\n";
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << "\n";
        std::cerr << "Place text.txt next to the .exe and rerun.\n";
        return 1;
    }

    ht.printTop3();
    ht.printTable();

    return 0;
}
