#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>
#include <algorithm>
#include <stdexcept>

using namespace std;

const int TABLE_SIZE = 10007;

struct Node {
    string word;
    int count;
    Node* next;
    Node(const string& w) : word(w), count(1), next(nullptr) {}
};

class HashTable {
private:
    vector<Node*> table;
    int totalWords;

    int hash(const string& word) const {
        unsigned long h = 5381;
        for (char c : word) {
            h = ((h << 5) + h) + static_cast<unsigned long>(c);
        }
        return static_cast<int>(h % TABLE_SIZE);
    }

public:
    HashTable() : table(TABLE_SIZE, nullptr), totalWords(0) {}

    ~HashTable() {
        for (int i = 0; i < TABLE_SIZE; ++i) {
            Node* current = table[i];
            while (current != nullptr) {
                Node* toDelete = current;
                current = current->next;
                delete toDelete;
            }
        }
    }

    void insert(const string& word) {
        if (word.empty()) {
            throw invalid_argument("Cannot insert empty string");
        }

        int index = hash(word);
        Node* current = table[index];

        while (current != nullptr) {
            if (current->word == word) {
                current->count++;
                return;
            }
            current = current->next;
        }

        Node* newNode = new Node(word);
        newNode->next = table[index];
        table[index] = newNode;
        totalWords++;
    }

    int find(const string& word) const {
        if (word.empty()) {
            throw invalid_argument("Cannot search empty string");
        }

        int index = hash(word);
        Node* current = table[index];

        while (current != nullptr) {
            if (current->word == word) {
                return current->count;
            }
            current = current->next;
        }
        return 0;
    }

    vector<pair<string, int>> getAllEntries() const {
        vector<pair<string, int>> entries;
        entries.reserve(totalWords);

        for (int i = 0; i < TABLE_SIZE; ++i) {
            Node* current = table[i];
            while (current != nullptr) {
                entries.push_back({current->word, current->count});
                current = current->next;
            }
        }
        return entries;
    }

    int size() const {
        return totalWords;
    }
};

bool isLetter(char c) {
    return isalpha(static_cast<unsigned char>(c));
}

string normalizeWord(const string& raw) {
    string result;
    for (char c : raw) {
        if (isLetter(c)) {
            result += static_cast<char>(tolower(static_cast<unsigned char>(c)));
        }
    }
    return result;
}

void processFile(const string& filename, HashTable& dict) {
    ifstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("Cannot open file: " + filename);
    }

    string currentWord;
    char c;

    while (file.get(c)) {
        if (isLetter(c)) {
            currentWord += c;
        } else {
            if (!currentWord.empty()) {
                string normalized = normalizeWord(currentWord);
                if (!normalized.empty()) {
                    dict.insert(normalized);
                }
                currentWord.clear();
            }
        }
    }

    if (!currentWord.empty()) {
        string normalized = normalizeWord(currentWord);
        if (!normalized.empty()) {
            dict.insert(normalized);
        }
    }

    file.close();
}

vector<pair<string, int>> getTopThree(const HashTable& dict) {
    auto entries = dict.getAllEntries();

    if (entries.empty()) {
        return {};
    }

    sort(entries.begin(), entries.end(),
        [](const auto& a, const auto& b) {
            return a.second > b.second;
        });

    size_t topCount = min(size_t(3), entries.size());
    return vector<pair<string, int>>(entries.begin(), entries.begin() + topCount);
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <filename.txt>" << endl;
        return 1;
    }

    try {
        HashTable dict;

        cout << "Processing file: " << argv[1] << "..." << endl;
        processFile(argv[1], dict);

        cout << "\nUnique words: " << dict.size() << endl;

        auto topThree = getTopThree(dict);

        cout << "\nTop 3 most frequent words:" << endl;
        if (topThree.empty()) {
            cout << "No words found in the file." << endl;
        } else {
            for (size_t i = 0; i < topThree.size(); ++i) {
                cout << i + 1 << ". \"" << topThree[i].first
                     << "\" — " << topThree[i].second << " times" << endl;
            }
        }

        cout << "\nLookup example:" << endl;
        string testWord;
        cout << "Enter a word to search (or 'q' to quit): ";

        while (cin >> testWord && testWord != "q") {
            try {
                testWord = normalizeWord(testWord);
                int freq = dict.find(testWord);
                if (freq > 0) {
                    cout << "Found: " << freq << " time(s)" << endl;
                } else {
                    cout << "Not found" << endl;
                }
            } catch (const exception& e) {
                cout << "Error: " << e.what() << endl;
            }
            cout << "Search again (or 'q' to quit): ";
        }

    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }

    return 0;
}
