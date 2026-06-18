#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "huffman.hpp"

std::string readFile(const char* filename) {
    std::ifstream file(filename, std::ios::in | std::ios::binary);
    if (!file.is_open()) return "";
    std::string content;
    char ch;
    while (file.get(ch)) {
        content += ch;
    }
    return content;
}
void writeTextFile(const char* filename, const std::string& text) {
    std::ofstream file(filename, std::ios::out | std::ios::binary);
    if (!file.is_open()) return;
    for (std::size_t i = 0; i < text.length(); ++i) {
        file.put(text[i]);
    }
}
void writeCompressedFile(const char* filename, const std::string& bits) {
    std::ofstream file(filename, std::ios::out | std::ios::binary);
    if (!file.is_open()) return;
    unsigned char current_byte = 0;
    int bit_count = 0;
    for (std::size_t i = 0; i < bits.length(); ++i) {
        current_byte <<= 1;
        if (bits[i] == '1') {
            current_byte |= 1;
        }
        bit_count++;
        if (bit_count == 8) {
            file.put(current_byte);
            current_byte = 0;
            bit_count = 0;
        }
    }
    if (bit_count > 0) {
        current_byte <<= (8 - bit_count);
        file.put(current_byte);
    }
}
std::string readCompressedFile(const char* filename, std::size_t totalBitsCount) {
    std::ifstream file(filename, std::ios::in | std::ios::binary);
    if (!file.is_open()) return "";
    std::string bits;
    unsigned char current_byte;
    std::size_t bits_read = 0;
    while (file.read(reinterpret_cast<char*>(&current_byte), 1)) {
        for (int i = 7; i >= 0; --i) {
            if (bits_read >= totalBitsCount) {
                break;
            }
            if ((current_byte >> i) & 1) {
                bits += '1';
            } else {
                bits += '0';
            }
            bits_read++;
        }
    }
    return bits;
}
void runPipeline(const char* srcFile, const char* binFile, const char* resFile) {
    std::string text = readFile(srcFile);
    int frequencies[256] = {0};
    for (std::size_t i = 0; i < text.length(); ++i) {
        unsigned char uc = static_cast<unsigned char>(text[i]);
        frequencies[uc]++;
    }
    HuffmanCoder coder;
    coder.buildTree(frequencies);
    std::cout << "Huffman tree built.\n";
    std::string encodedBits = coder.encode(text);
    std::size_t totalBitsCount = encodedBits.length();
    std::cout << "Text encoded. Bits: " << totalBitsCount << "\n";
    writeCompressedFile(binFile, encodedBits);
    std::cout << "Compressed file saved: " << binFile << "\n";
    std::string bitsFromBinary = readCompressedFile(binFile, totalBitsCount);
    std::cout << "Binary data read.\n";
    std::string decodedText = coder.decode(bitsFromBinary);
    writeTextFile(resFile, decodedText);
    std::cout << "Decoding completed. Restored file: " << resFile << "\n";
    std::ifstream inSize(srcFile, std::ios::ate | std::ios::binary);
    std::ifstream outSize(binFile, std::ios::ate | std::ios::binary);
    std::ifstream resSize(resFile, std::ios::ate | std::ios::binary);
    if (inSize.is_open() && outSize.is_open() && resSize.is_open()) {
        std::cout << "\nOriginal: " << inSize.tellg() << " bytes\n";
        std::cout << "Compressed: " << outSize.tellg() << " bytes\n";
        std::cout << "Restored: " << resSize.tellg() << " bytes\n";
        if (inSize.tellg() == resSize.tellg()) {
            std::cout << "Success: No data loss.\n";
        } else {
            std::cout << "Warning: File sizes do not match.\n";
        }
    }
}
int main() {
    std::string line;
    while (true) {
        std::cout << "> ";
        if (!std::getline(std::cin, line)) {
            break;
        }
        if (line.empty()) continue;
        std::istringstream iss(line);
        std::string command;
        iss >> command;
        if (command == "exit") {
            break;
        } else if (command == "run") {
            std::string src, bin, res;
            if (iss >> src >> bin >> res) {
                runPipeline(src.c_str(), bin.c_str(), res.c_str());
            } else {
                std::cout << "Usage: run <source_file> <binary_file> <restored_file>\n";
            }
        } else {
            std::cout << "Unknown command. Available commands: run, exit\n";
        }
    }
    return 0;
}
