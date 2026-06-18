#include "HashTable.hpp"

HashTable::HashTable(int size) {
    if (size <= 0) {
        throw "Incorrect table size";
    }

    tableSize = size;
    wordsCount = 0;
    uniqueWordsCount = 0;
    table.resize(tableSize);
}

HashTable::~HashTable() {
    clear();
}

int HashTable::hashFunction(std::string word) const {
    unsigned int hash = 0;

    for (int i = 0; i < static_cast<int>(word.length()); i++) {
        hash = (hash * 31 + static_cast<unsigned char>(word[i])) % tableSize;
    }

    return static_cast<int>(hash);
}

bool HashTable::isCorrectWord(std::string word) const {
    return word.length() > 0;
}

WordNode *HashTable::getNode(std::string word) {
    if (!isCorrectWord(word)) {
        return 0;
    }

    int index = hashFunction(word);

    for (std::list<WordNode>::iterator it = table[index].begin(); it != table[index].end(); ++it) {
        if (it->word == word) {
            return &(*it);
        }
    }

    return 0;
}

const WordNode *HashTable::getNode(std::string word) const {
    if (!isCorrectWord(word)) {
        return 0;
    }

    int index = hashFunction(word);

    for (std::list<WordNode>::const_iterator it = table[index].begin(); it != table[index].end(); ++it) {
        if (it->word == word) {
            return &(*it);
        }
    }

    return 0;
}

void HashTable::insert(std::string word) {
    word = prepareWord(word);

    if (!isCorrectWord(word)) {
        return;
    }

    WordNode *node = getNode(word);

    if (node != 0) {
        node->count = node->count + 1;
        wordsCount = wordsCount + 1;
        return;
    }

    int index = hashFunction(word);
    WordNode newNode;

    newNode.word = word;
    newNode.count = 1;

    table[index].push_back(newNode);

    wordsCount = wordsCount + 1;
    uniqueWordsCount = uniqueWordsCount + 1;
}

bool HashTable::search(std::string word, int &count) const {
    word = prepareWord(word);
    const WordNode *node = getNode(word);

    if (node == 0) {
        count = 0;
        return false;
    }

    count = node->count;
    return true;
}

bool HashTable::remove(std::string word) {
    word = prepareWord(word);

    if (!isCorrectWord(word)) {
        return false;
    }

    int index = hashFunction(word);

    for (std::list<WordNode>::iterator it = table[index].begin(); it != table[index].end(); ++it) {
        if (it->word == word) {
            wordsCount = wordsCount - it->count;
            uniqueWordsCount = uniqueWordsCount - 1;
            table[index].erase(it);
            return true;
        }
    }

    return false;
}

void HashTable::print() const {
    if (isEmpty()) {
        std::cout << "Dictionary is empty" << std::endl;
        return;
    }

    for (int i = 0; i < tableSize; i++) {
        for (std::list<WordNode>::const_iterator it = table[i].begin(); it != table[i].end(); ++it) {
            std::cout << it->word << " : " << it->count << std::endl;
        }
    }
}

void HashTable::printTopThree() const {
    if (isEmpty()) {
        std::cout << "Dictionary is empty" << std::endl;
        return;
    }

    std::vector<std::string> topWords(3, "");
    std::vector<int> topCounts(3, 0);

    for (int i = 0; i < tableSize; i++) {
        for (std::list<WordNode>::const_iterator it = table[i].begin(); it != table[i].end(); ++it) {
            for (int j = 0; j < 3; j++) {
                if (it->count > topCounts[j]) {
                    for (int k = 2; k > j; k--) {
                        topCounts[k] = topCounts[k - 1];
                        topWords[k] = topWords[k - 1];
                    }

                    topCounts[j] = it->count;
                    topWords[j] = it->word;
                    break;
                }
            }
        }
    }

    std::cout << "Top 3 words:" << std::endl;

    for (int i = 0; i < 3; i++) {
        if (topCounts[i] > 0) {
            std::cout << i + 1 << ". " << topWords[i] << " : " << topCounts[i] << std::endl;
        }
    }
}

void HashTable::clear() {
    for (int i = 0; i < tableSize; i++) {
        table[i].clear();
    }

    wordsCount = 0;
    uniqueWordsCount = 0;
}

int HashTable::getWordsCount() const {
    return wordsCount;
}

int HashTable::getUniqueWordsCount() const {
    return uniqueWordsCount;
}

bool HashTable::isEmpty() const {
    return wordsCount == 0;
}

bool isWordSymbol(char symbol) {
    if (symbol >= 'a' && symbol <= 'z') {
        return true;
    }

    if (symbol >= 'A' && symbol <= 'Z') {
        return true;
    }

    return false;
}

char toLowerSymbol(char symbol) {
    if (symbol >= 'A' && symbol <= 'Z') {
        return static_cast<char>(symbol + ('a' - 'A'));
    }

    return symbol;
}

std::string prepareWord(std::string word) {
    std::string result = "";

    for (int i = 0; i < static_cast<int>(word.length()); i++) {
        if (isWordSymbol(word[i])) {
            result = result + toLowerSymbol(word[i]);
        }
    }

    return result;
}

void addTextToTable(std::string text, HashTable &table) {
    std::string word = "";

    for (int i = 0; i < static_cast<int>(text.length()); i++) {
        if (isWordSymbol(text[i])) {
            word = word + toLowerSymbol(text[i]);
        } else {
            if (word.length() > 0) {
                table.insert(word);
                word = "";
            }
        }
    }

    if (word.length() > 0) {
        table.insert(word);
    }
}

void readFile(std::string fileName, HashTable &table) {
    std::ifstream file(fileName.c_str());

    if (!file.is_open()) {
        throw "File was not opened";
    }

    std::string line;
    int oldWordsCount = table.getWordsCount();

    while (getline(file, line)) {
        addTextToTable(line, table);
    }

    file.close();

    if (table.getWordsCount() == oldWordsCount) {
        throw "File does not contain words";
    }
}

bool canOpenFile(std::string fileName) {
    std::ifstream file(fileName.c_str());

    if (file.is_open()) {
        file.close();
        return true;
    }

    return false;
}
