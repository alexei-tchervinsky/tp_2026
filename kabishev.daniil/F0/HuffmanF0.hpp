#ifndef HUFFMAN_HPP
#define HUFFMAN_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <map>
#include <memory>
#include <string>
#include <stdexcept>

class HuffmanNode {
public:
    char ch;
    size_t freq;
    std::shared_ptr<HuffmanNode> left;
    std::shared_ptr<HuffmanNode> right;

    HuffmanNode(char character, size_t frequency)
        : ch(character), freq(frequency), left(nullptr), right(nullptr) {}

    HuffmanNode(size_t frequency, std::shared_ptr<HuffmanNode> l, std::shared_ptr<HuffmanNode> r)
        : ch('\0'), freq(frequency), left(l), right(r) {}
};

struct CompareNodes {
    bool operator()(const std::shared_ptr<HuffmanNode>& a, const std::shared_ptr<HuffmanNode>& b) {
        return a->freq > b->freq;
    }
};

class HuffmanArchiver {
private:
    std::map<char, std::string> huffmanCodes_;
    std::map<char, size_t> frequencies_;

    void generateCodes(const std::shared_ptr<HuffmanNode>& root, const std::string& str) {
        if (!root) return;

        if (!root->left && !root->right) {
            huffmanCodes_[root->ch] = str.empty() ? "0" : str;
        }

        generateCodes(root->left, str + "0");
        generateCodes(root->right, str + "1");
    }

public:
    void compress(const std::string& inputPath, const std::string& outputPath) {
        std::ifstream inFile(inputPath, std::ios::binary);
        if (!inFile.is_open()) {
            throw std::runtime_error("Exception: Cannot open input file for compression: " + inputPath);
        }

        frequencies_.clear();
        huffmanCodes_.clear();

        char ch;
        size_t totalChars = 0;
        while (inFile.get(ch)) {
            frequencies_[ch]++;
            totalChars++;
        }

        if (totalChars == 0) {
            throw std::invalid_argument("Exception: Input file is empty. Cannot perform Huffman coding.");
        }

        std::priority_queue<std::shared_ptr<HuffmanNode>,
                            std::vector<std::shared_ptr<HuffmanNode>>,
                            CompareNodes> minHeap;

        for (const auto& pair : frequencies_) {
            minHeap.push(std::make_shared<HuffmanNode>(pair.first, pair.second));
        }

        if (minHeap.size() == 1) {
            auto singleNode = minHeap.top();
            auto dummyRoot = std::make_shared<HuffmanNode>(singleNode->freq, singleNode, nullptr);
            minHeap.pop();
            minHeap.push(dummyRoot);
        } else {
            while (minHeap.size() > 1) {
                auto left = minHeap.top(); minHeap.pop();
                auto right = minHeap.top(); minHeap.pop();
                auto top = std::make_shared<HuffmanNode>(left->freq + right->freq, left, right);
                minHeap.push(top);
            }
        }

        generateCodes(minHeap.top(), "");

        std::ofstream outFile(outputPath, std::ios::binary);
        if (!outFile.is_open()) {
            throw std::runtime_error("Exception: Cannot open output archive file: " + outputPath);
        }

        size_t tableSize = frequencies_.size();
        outFile.write(reinterpret_cast<const char*>(&tableSize), sizeof(tableSize));
        for (const auto& pair : frequencies_) {
            outFile.put(pair.first);
            size_t freq = pair.second;
            outFile.write(reinterpret_cast<const char*>(&freq), sizeof(freq));
        }

        inFile.clear();
        inFile.seekg(0, std::ios::beg);

        unsigned char bitBuffer = 0;
        int bitCount = 0;

        while (inFile.get(ch)) {
            const std::string& code = huffmanCodes_[ch];
            for (char bit : code) {
                bitBuffer <<= 1;
                if (bit == '1') {
                    bitBuffer |= 1;
                }
                bitCount++;
                if (bitCount == 8) {
                    outFile.put(bitBuffer);
                    bitBuffer = 0;
                    bitCount = 0;
                }
            }
        }

        if (bitCount > 0) {
            bitBuffer <<= (8 - bitCount);
            outFile.put(bitBuffer);
            outFile.put(static_cast<unsigned char>(bitCount));
        } else {
            outFile.put(static_cast<unsigned char>(8));
        }

        inFile.close();
        outFile.close();
    }

    void decompress(const std::string& inputPath, const std::string& outputPath) {
        std::ifstream inFile(inputPath, std::ios::binary);
        if (!inFile.is_open()) {
            throw std::runtime_error("Exception: Cannot open archive file for decompress: " + inputPath);
        }

        size_t tableSize = 0;
        if (!inFile.read(reinterpret_cast<char*>(&tableSize), sizeof(tableSize))) {
            throw std::runtime_error("Exception: Corrupted archive header (cannot read table size).");
        }

        frequencies_.clear();
        for (size_t i = 0; i < tableSize; ++i) {
            char ch;
            if (!inFile.get(ch)) {
                throw std::runtime_error("Exception: Corrupted archive header (cannot read character).");
            }
            size_t freq = 0;
            if (!inFile.read(reinterpret_cast<char*>(&freq), sizeof(freq))) {
                throw std::runtime_error("Exception: Corrupted archive header (cannot read frequency).");
            }
            frequencies_[ch] = freq;
        }

        if (frequencies_.empty()) {
            throw std::runtime_error("Exception: Empty frequency table in archive metadata.");
        }

        std::priority_queue<std::shared_ptr<HuffmanNode>,
                            std::vector<std::shared_ptr<HuffmanNode>>,
                            CompareNodes> minHeap;

        size_t totalChars = 0;
        for (const auto& pair : frequencies_) {
            minHeap.push(std::make_shared<HuffmanNode>(pair.first, pair.second));
            totalChars += pair.second;
        }

        if (minHeap.size() == 1) {
            auto singleNode = minHeap.top();
            auto dummyRoot = std::make_shared<HuffmanNode>(singleNode->freq, singleNode, nullptr);
            minHeap.pop();
            minHeap.push(dummyRoot);
        } else {
            while (minHeap.size() > 1) {
                auto left = minHeap.top(); minHeap.pop();
                auto right = minHeap.top(); minHeap.pop();
                auto top = std::make_shared<HuffmanNode>(left->freq + right->freq, left, right);
                minHeap.push(top);
            }
        }

        auto root = minHeap.top();
        std::ofstream outFile(outputPath, std::ios::binary);
        if (!outFile.is_open()) {
            throw std::runtime_error("Exception: Cannot open output file for restoration: " + outputPath);
        }

        auto currentNode = root;
        size_t decodedChars = 0;
        char byte;

        while (inFile.get(byte) && decodedChars < totalChars) {
            for (int i = 7; i >= 0; --i) {
                int bit = (byte >> i) & 1;
                if (bit == 0) {
                    currentNode = currentNode->left;
                } else {
                    currentNode = currentNode->right;
                }

                if (!currentNode) {
                    throw std::runtime_error("Exception: Corrupted bitstream navigation.");
                }

                if (!currentNode->left && !currentNode->right) {
                    outFile.put(currentNode->ch);
                    decodedChars++;
                    currentNode = root;
                    if (decodedChars == totalChars) {
                        break;
                    }
                }
            }
        }

        if (decodedChars < totalChars) {
            throw std::runtime_error("Exception: Archive ended unexpectedly.");
        }

        inFile.close();
        outFile.close();
    }
};

#endif
