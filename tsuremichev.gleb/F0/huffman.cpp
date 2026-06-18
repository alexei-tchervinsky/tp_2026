#include "huffman.hpp"
#include <queue>
#include <stdexcept>
#include <iostream>

HuffmanNode::HuffmanNode(char ch, size_t freq)
    : character(ch), frequency(freq), left(nullptr), right(nullptr) {}

bool NodeComparator::operator()(const std::unique_ptr<HuffmanNode> &lhs, const std::unique_ptr<HuffmanNode> &rhs) const
{
  return lhs->frequency > rhs->frequency;
}

void HuffmanEncoder::generateCodes(const HuffmanNode *node, const std::string &currentCode)
{
  if (!node)
    return;

  if (!node->left && !node->right)
  {
    codeTable[node->character] = currentCode;
    return;
  }
  generateCodes(node->left.get(), currentCode + "0");
  generateCodes(node->right.get(), currentCode + "1");
}

void HuffmanEncoder::buildTree(const std::string &text)
{
  if (text.empty())
  {
    throw std::invalid_argument("Инициализация невозможна: входная строка пуста.");
  }

  treeRoot.reset();
  codeTable.clear();

  std::map<char, size_t> frequencies;
  for (char ch : text)
  {
    frequencies[ch]++;
  }

  std::priority_queue<std::unique_ptr<HuffmanNode>,
                      std::vector<std::unique_ptr<HuffmanNode>>,
                      NodeComparator>
      priorityQueue;

  for (std::map<char, size_t>::const_iterator it = frequencies.begin(); it != frequencies.end(); ++it)
  {
    priorityQueue.push(std::make_unique<HuffmanNode>(it->first, it->second));
  }

  while (priorityQueue.size() > 1)
  {
    auto leftNode = std::move(const_cast<std::unique_ptr<HuffmanNode> &>(priorityQueue.top()));
    priorityQueue.pop();

    auto rightNode = std::move(const_cast<std::unique_ptr<HuffmanNode> &>(priorityQueue.top()));
    priorityQueue.pop();

    auto parentNode = std::make_unique<HuffmanNode>('\0', leftNode->frequency + rightNode->frequency);
    parentNode->left = std::move(leftNode);
    parentNode->right = std::move(rightNode);

    priorityQueue.push(std::move(parentNode));
  }

  if (!priorityQueue.empty())
  {
    treeRoot = std::move(const_cast<std::unique_ptr<HuffmanNode> &>(priorityQueue.top()));
    priorityQueue.pop();
  }

  if (treeRoot && !treeRoot->left && !treeRoot->right)
  {
    codeTable[treeRoot->character] = "0";
    return;
  }

  generateCodes(treeRoot.get(), "");
}

std::string HuffmanEncoder::encode(const std::string &text) const
{
  if (!treeRoot)
    throw std::runtime_error("Операция невозможна: дерево не построено.");

  std::string encodedResult;
  for (char ch : text)
  {
    encodedResult += codeTable.at(ch);
  }
  return encodedResult;
}

std::string HuffmanEncoder::decode(const std::string &bitstream) const
{
  if (!treeRoot)
    throw std::runtime_error("Операция невозможна: дерево не построено.");

  std::string decodedResult;
  const HuffmanNode *currentNode = treeRoot.get();

  for (char bit : bitstream)
  {
    if (bit == '0')
      currentNode = currentNode->left.get();
    else if (bit == '1')
      currentNode = currentNode->right.get();
    else
      throw std::runtime_error("Ошибка декодирования: невалидный символ в бинарном потоке.");

    if (!currentNode->left && !currentNode->right)
    {
      decodedResult += currentNode->character;
      currentNode = treeRoot.get();
    }
  }
  return decodedResult;
}

void HuffmanEncoder::printTable() const
{
  for (std::map<char, std::string>::const_iterator it = codeTable.begin(); it != codeTable.end(); ++it)
  {
    unsigned char ch = it->first;
    const std::string &code = it->second;

    if (ch == ' ')
      std::cout << "  ' ' (пробел) : " << code << "\n";
    else if (ch == '\n')
      std::cout << "  '\\n' (перенос): " << code << "\n";
    else
      std::cout << "  '" << ch << "'          : " << code << "\n";
  }
}
