#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <cctype>

struct WordFreq {
    std::string word;
    size_t count;
};

std::string cleanAndLower(const std::string& word) {
    std::string cleanWord = "";
    for (char c : word) {
        if (std::isalpha(static_cast<unsigned char>(c))) {
            cleanWord += static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
        }
    }
    return cleanWord;
}

void processFile(const std::string& filename, std::unordered_map<std::string, size_t>& ht) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "The file can't be opened: " << filename << "\n";
        return;
    }
    std::string word;
    while (file >> word) {
        std::string clean = cleanAndLower(word);
        if (!clean.empty()) {
            ht[clean]++;
        }
    }
    std::cout << "File processed successfully.\n";
}

void printTopThree(const std::unordered_map<std::string, size_t>& ht) {
   if (ht.empty()) {
        std::cout << "Table is empty.\n";
        return;
    }
    std::vector<WordFreq> frequencies;
    frequencies.reserve(ht.size());
    for (const auto& pair : ht) {
        const auto& word = pair.first;
        const auto& count = pair.second;
        frequencies.push_back({word, count});
    }
    std::sort(frequencies.begin(), frequencies.end(), [](const WordFreq& a, const WordFreq& b) {
        if (a.count != b.count) {
            return a.count > b.count;
        }
        return a.word < b.word;
    });
    size_t limit = std::min(frequencies.size(), size_t(3));
    for (size_t i = 0; i < limit; ++i) {
        std::cout << i + 1 << ". " << frequencies[i].word << ": " << frequencies[i].count << "\n";
    }
}
void printAll(const std::unordered_map<std::string, size_t>& ht) {
    if (ht.empty()) {
        std::cout << "Hash table is empty \n";
        return;
    }
    for (const auto& pair : ht) {
        const auto& word = pair.first;
        const auto& count = pair.second;
        std::cout << word << " -> " << count << "\n";
    }
}
int main() {
    std::unordered_map<std::string, size_t> hashTable;

    std::string command;
    std::cout << "Commands: read <filename> | search <word> | remove <word> | print | top3\n\n> ";

   while (std::cin >> command) {
        if (command == "read") {
            std::string filename;
            std::cin >> filename;
            processFile(filename, hashTable);
        }
        else if (command == "search") {
            std::string word;
            std::cin >> word;
            std::string clean = cleanAndLower(word);

            auto it = hashTable.find(clean);
            if (it != hashTable.end()) {
                std::cout << "Found! Frequency of '" << clean << "': " << it->second << "\n";
            } else {
                std::cout << "'" << clean << "' not found in the table.\n";
            }
        }
        else if (command == "remove") {
            std::string word;
            std::cin >> word;
            std::string clean = cleanAndLower(word);

            if (hashTable.erase(clean)) {
                std::cout << "Successfully removed '" << clean << "'\n";
            } else {
                std::cout << "'" << clean << "' was not in the table.\n";
            }
        }
        else if (command == "print") {
            printAll(hashTable);
        }
        else if (command == "top3") {
            printTopThree(hashTable);
        }
        else {
            std::cout << "Unknown command. Available: read, search, remove, print, top3\n";
        }
        std::cout << "\n> ";
    }
    return 0;
}
