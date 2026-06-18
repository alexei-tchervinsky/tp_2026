#ifndef HUFFMAN_HPP
#define HUFFMAN_HPP

#include <string>
#include <vector>
#include <map>
#include <memory>

struct HuffmanNode
{
  char character;
  size_t frequency;
  std::unique_ptr<HuffmanNode> left;
  std::unique_ptr<HuffmanNode> right;

  HuffmanNode(char ch, size_t freq);
};

struct NodeComparator
{
  bool operator()(const std::unique_ptr<HuffmanNode> &lhs, const std::unique_ptr<HuffmanNode> &rhs) const;
};

class HuffmanEncoder
{
private:
  std::unique_ptr<HuffmanNode> treeRoot;
  std::map<char, std::string> codeTable;

  void generateCodes(const HuffmanNode *node, const std::string &currentCode);

public:
  HuffmanEncoder() = default;

  void buildTree(const std::string &text);
  std::string encode(const std::string &text) const;
  std::string decode(const std::string &bitstream) const;
  void printTable() const;
};

#endif // HUFFMAN_HPP
