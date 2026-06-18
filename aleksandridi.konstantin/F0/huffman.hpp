#ifndef HUFFMAN_HPP
#define HUFFMAN_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <queue>
#include <memory>
#include <vector>
#include "huffman_node.hpp"

class HuffmanCoder {
private:
    std::shared_ptr<HuffmanNode> root_;
    std::unordered_map<std::string, std::string> codesTable_;
    void generateCodes(std::shared_ptr<HuffmanNode> node, const std::string& currentCode);
    void clearTree(std::shared_ptr<HuffmanNode> node);
public:
    HuffmanCoder();
    ~HuffmanCoder();
    void buildTree(const int frequencies[256]);
    void buildTree(const std::string& text);
    std::string getCode(unsigned char ch) const;
    void decodeFromFile(std::ifstream& inFile, std::ofstream& outFile);
    std::string encode(const std::string& text) const;
    std::string decode(const std::string& encodedText) const;
    void printCodes() const;
};

HuffmanCoder::HuffmanCoder() : root_(nullptr) {}
HuffmanCoder::~HuffmanCoder() {
    clearTree(root_);
}
void HuffmanCoder::clearTree(std::shared_ptr<HuffmanNode> node) {
    if (!node) return;
    clearTree(node->left_);
    clearTree(node->right_);
    root_ = nullptr;
}
void HuffmanCoder::generateCodes(std::shared_ptr<HuffmanNode> node, const std::string& currentCode) {
    if (!node) return;
    if (!node->left_ && !node->right_) {
        unsigned char uc = static_cast<unsigned char>(node->symbol_);
        char key[2] = { static_cast<char>(uc), '\0' };
        codesTable_[std::string(key)] = currentCode;
        return;
    }
    generateCodes(node->left_, currentCode + "0");
    generateCodes(node->right_, currentCode + "1");
}
void HuffmanCoder::buildTree(const int frequencies[256]) {
    clearTree(root_);
    codesTable_.clear();
    std::priority_queue<NodeWrapper> pq;
    for (int i = 0; i < 256; ++i) {
        if (frequencies[i] > 0) {
            auto node = std::make_shared<HuffmanNode>(static_cast<char>(i), frequencies[i]);
            pq.push(NodeWrapper(node));
        }
    }
    if (pq.empty()) return;
    if (pq.size() == 1) {
        auto single = pq.top().node_;
        pq.pop();
        root_ = std::make_shared<HuffmanNode>('\0', single->freq_, single, nullptr);
        generateCodes(root_, "0");
        return;
    }
    while (pq.size() > 1) {
        auto first = pq.top().node_; pq.pop();
        auto second = pq.top().node_; pq.pop();

        auto parent = std::make_shared<HuffmanNode>('\0', first->freq_ + second->freq_, first, second);
        pq.push(NodeWrapper(parent));
    }
    root_ = pq.top().node_;
    generateCodes(root_, "");
}
void HuffmanCoder::buildTree(const std::string& text) {
    int frequencies[256] = {0};
    for (std::size_t i = 0; i < text.length(); ++i) {
        unsigned char uc = static_cast<unsigned char>(text[i]);
        frequencies[uc]++;
    }
    buildTree(frequencies);
}
std::string HuffmanCoder::getCode(unsigned char ch) const {
    char key[2] = { static_cast<char>(ch), '\0' };
    auto it = codesTable_.find(std::string(key));
    if (it != codesTable_.end()) {
        return it->second;
    }
    return "";
}
void HuffmanCoder::decodeFromFile(std::ifstream& inFile, std::ofstream& outFile) {
    if (!root_ || !inFile.is_open() || !outFile.is_open()) return;

    std::shared_ptr<HuffmanNode> current = root_;
    char ch;
    while (inFile.get(ch)) {
        unsigned char byte = static_cast<unsigned char>(ch);
        for (int i = 7; i >= 0; --i) {
            bool bit = (byte >> i) & 1;
            if (!bit) {
                current = current->left_;
            } else {
                current = current->right_;
            }
            if (current && !current->left_ && !current->right_) {
                outFile.put(current->symbol_);
                current = root_;
            }
        }
    }
}

std::string HuffmanCoder::encode(const std::string& text) const {
    std::string encodedStr = "";
    for (std::size_t i = 0; i < text.length(); ++i) {
        unsigned char uc = static_cast<unsigned char>(text[i]);
        char key[2] = { static_cast<char>(uc), '\0' };

        auto it = codesTable_.find(std::string(key));
        if (it != codesTable_.end()) {
            encodedStr = encodedStr + it->second;
        }
    }
    return encodedStr;
}

std::string HuffmanCoder::decode(const std::string& encodedText) const {
    std::string decodedStr = "";
    if (!root_) return decodedStr;

    std::shared_ptr<HuffmanNode> current = root_;
    for (std::size_t i = 0; i < encodedText.length(); ++i) {
        if (encodedText[i] == '0') current = current->left_;
        else if (encodedText[i] == '1') current = current->right_;

        if (current && !current->left_ && !current->right_) {
            char sym[2] = { current->symbol_, '\0' };
            decodedStr = decodedStr + sym;
            current = root_;
        }
    }
    return decodedStr;
}

void HuffmanCoder::printCodes() const {
    std::cout << "\n--- Huffman Codes Table ---\n";
    for (const auto& pair : codesTable_) {
        std::cout << "[" << pair.first << ": " << pair.second << "]\n";
    }
    std::cout << "---------------------------\n";
}

#endif // HUFFMAN_HPP
