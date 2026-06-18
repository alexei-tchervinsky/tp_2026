#include "HashTable.hpp"

std::string getFileName(int argc, char *argv[]) {
    if (argc > 1) {
        return argv[1];
    }

    if (canOpenFile("input.txt")) {
        return "input.txt";
    }

    if (canOpenFile("../input.txt")) {
        return "../input.txt";
    }

    return "input.txt";
}

void printLine() {
    std::cout << "----------------------------------------" << std::endl;
}

void showSearchResult(HashTable &table, std::string word) {
    int count = 0;

    if (table.search(word, count)) {
        std::cout << "Search " << word << ": found, count = " << count << std::endl;
    } else {
        std::cout << "Search " << word << ": not found" << std::endl;
    }
}

void showDeleteResult(HashTable &table, std::string word) {
    if (table.remove(word)) {
        std::cout << "Delete " << word << ": deleted" << std::endl;
    } else {
        std::cout << "Delete " << word << ": not found" << std::endl;
    }
}

void runFileTask(std::string fileName) {
    HashTable table(101);

    std::cout << "Part 1. Reading text from file" << std::endl;
    std::cout << "File name: " << fileName << std::endl;

    readFile(fileName, table);

    std::cout << "All words: " << table.getWordsCount() << std::endl;
    std::cout << "Unique words: " << table.getUniqueWordsCount() << std::endl;

    printLine();
    std::cout << "Frequency dictionary:" << std::endl;
    table.print();

    printLine();
    table.printTopThree();

    printLine();
    std::cout << "Searching words from file task:" << std::endl;
    showSearchResult(table, "table");
    showSearchResult(table, "word");
    showSearchResult(table, "nothing");

    printLine();
    std::cout << "Deleting words from file task:" << std::endl;
    showDeleteResult(table, "nothing");
    showDeleteResult(table, "table");
    showSearchResult(table, "table");

    printLine();
    std::cout << "Dictionary after deleting:" << std::endl;
    table.print();

    printLine();
    std::cout << "Top 3 after deleting:" << std::endl;
    table.printTopThree();
}

void runSimpleOperationsTest() {
    HashTable table(11);
    int count = 0;

    std::cout << "Part 2. Basic operations test" << std::endl;

    table.insert("cat");
    table.insert("dog");
    table.insert("cat");
    table.insert("bird");
    table.insert("dog");
    table.insert("cat");

    std::cout << "After insert:" << std::endl;
    table.print();

    if (table.search("cat", count)) {
        std::cout << "cat count = " << count << std::endl;
    }

    if (!table.search("fish", count)) {
        std::cout << "fish was not found" << std::endl;
    }

    if (table.remove("dog")) {
        std::cout << "dog was deleted" << std::endl;
    }

    if (!table.remove("fish")) {
        std::cout << "fish was not deleted" << std::endl;
    }

    std::cout << "After delete:" << std::endl;
    table.print();
    table.printTopThree();
}

void runTextProcessingTest() {
    HashTable table(17);

    std::cout << "Part 3. Text processing test" << std::endl;

    addTextToTable("Hello, hello! World... 123 world", table);

    std::cout << "Result:" << std::endl;
    table.print();
    table.printTopThree();
}

void runClearTest() {
    HashTable table(7);

    std::cout << "Part 4. Clear test" << std::endl;

    table.insert("one");
    table.insert("two");
    table.insert("two");

    std::cout << "Before clear:" << std::endl;
    table.print();

    table.clear();

    std::cout << "After clear:" << std::endl;
    table.print();
}

void runErrorTest() {
    std::cout << "Part 5. Error processing test" << std::endl;

    try {
        HashTable table(0);
    } catch (const char *error) {
        std::cout << "Error: " << error << std::endl;
    }

    try {
        HashTable table(10);
        readFile("file_not_found.txt", table);
    } catch (const char *error) {
        std::cout << "Error: " << error << std::endl;
    }
}

int main(int argc, char *argv[]) {
    setlocale(LC_ALL, "");

    std::cout << "Frequency dictionary. Batch mode" << std::endl;
    printLine();

    try {
        std::string fileName = getFileName(argc, argv);

        runFileTask(fileName);
        printLine();
        runSimpleOperationsTest();
        printLine();
        runTextProcessingTest();
        printLine();
        runClearTest();
        printLine();
        runErrorTest();
        printLine();

        std::cout << "Program finished" << std::endl;
    } catch (const char *error) {
        std::cout << "Error: " << error << std::endl;
    }

    return 0;
}
