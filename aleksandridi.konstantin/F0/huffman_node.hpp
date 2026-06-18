#ifndef HUFFMAN_NODE_HPP
#define HUFFMAN_NODE_HPP

#include <memory>

struct HuffmanNode {
    char symbol_;
    int freq_;
    std::shared_ptr<HuffmanNode> left_;
    std::shared_ptr<HuffmanNode> right_;
    HuffmanNode(char symbol, int freq, std::shared_ptr<HuffmanNode> left = nullptr, std::shared_ptr<HuffmanNode> right = nullptr);
};
HuffmanNode::HuffmanNode(char symbol, int freq, std::shared_ptr<HuffmanNode> left, std::shared_ptr<HuffmanNode> right)
    : symbol_(symbol), freq_(freq), left_(left), right_(right) {}
struct NodeWrapper {
    std::shared_ptr<HuffmanNode> node_;
    NodeWrapper(std::shared_ptr<HuffmanNode> node = nullptr);
    bool operator<(const NodeWrapper& other) const;
    bool operator>(const NodeWrapper& other) const;
    bool operator==(const NodeWrapper& other) const;
    bool operator!=(const NodeWrapper& other) const;
};
NodeWrapper::NodeWrapper(std::shared_ptr<HuffmanNode> node) : node_(node) {}
bool NodeWrapper::operator<(const NodeWrapper& other) const {
    if (!node_ || !other.node_) return false;
    if (node_->freq_ == other.node_->freq_) {
        return node_ > other.node_;
    }
    return node_->freq_ > other.node_->freq_;
}
bool NodeWrapper::operator>(const NodeWrapper& other) const {
    if (!node_ || !other.node_) return false;
    if (node_->freq_ == other.node_->freq_) {
        return node_ < other.node_;
    }
    return node_->freq_ < other.node_->freq_;
}
bool NodeWrapper::operator==(const NodeWrapper& other) const {
    if (!node_ || !other.node_) return false;
    return node_->freq_ == other.node_->freq_;
}
bool NodeWrapper::operator!=(const NodeWrapper& other) const {
    return !(*this == other);
}
#endif // HUFFMAN_NODE_HPP
