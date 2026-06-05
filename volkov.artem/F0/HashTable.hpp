#ifndef HASH_TABLE_HPP
#define HASH_TABLE_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <clocale>

struct WordNode {
    std::string word;
    int count;
};

class HashTable {
private:
    std::vector<std::list<WordNode> > table;
    int tableSize;
    int wordsCount;
    int uniqueWordsCount;

    int hashFunction(std::string word) const;

    WordNode *getNode(std::string word);

    const WordNode *getNode(std::string word) const;

    bool isCorrectWord(std::string word) const;

public:
    HashTable(int size);

    ~HashTable();

    void insert(std::string word);

    bool search(std::string word, int &count) const;

    bool remove(std::string word);

    void print() const;

    void printTopThree() const;

    void clear();

    int getWordsCount() const;

    int getUniqueWordsCount() const;

    bool isEmpty() const;
};

bool isWordSymbol(char symbol);

char toLowerSymbol(char symbol);

std::string prepareWord(std::string word);

void addTextToTable(std::string text, HashTable &table);

void readFile(std::string fileName, HashTable &table);

bool canOpenFile(std::string fileName);

#endif
