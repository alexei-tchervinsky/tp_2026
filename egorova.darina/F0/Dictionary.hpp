#ifndef DICTIONARY_HPP
#define DICTIONARY_HPP

#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <algorithm>
#include "Nodes.hpp"

class Dictionary {
public:
    Dictionary() : mRoot(nullptr) {}

    ~Dictionary() {
        destroyTree(mRoot);
    }

    void insert(const std::string& key, const std::string& translation) {
        if (key.empty()) throw std::invalid_argument("Key cannot be empty");
        if (!mRoot) {
            mRoot = createLeaf(key, translation);
            return;
        }
        SplitResult* res = insertRecursive(mRoot, key, translation);
        if (res) {
            InternalNode* newRoot = new InternalNode();
            newRoot->mKeys.push_back(res->key);
            newRoot->mChildren.push_back(res->left);
            newRoot->mChildren.push_back(res->right);
            mRoot = newRoot;
            delete res;
        }
    }

    const TranslationList* search(const std::string& key) const {
        Node* leaf = findLeaf(mRoot, key);
        if (leaf) {
            LeafNode* ln = static_cast<LeafNode*>(leaf);
            if (ln->mKey == key) return &(ln->mData);
        }
        return nullptr;
    }

    void remove(const std::string& key) {
        if (!mRoot || key.empty()) return;

        bool hole = false;
        removeRecursive(mRoot, key, hole);

        // Если корень стал внутренним узлом без ключей,
        // его ребенок становится новым корнем
        if (!mRoot->isLeaf()) {
            InternalNode* internal = static_cast<InternalNode*>(mRoot);
            if (internal->mChildren.size() == 1) {
                Node* oldRoot = mRoot;
                mRoot = internal->mChildren[0];
                internal->mChildren.clear();
                delete oldRoot;
            }
        } else if (hole) { // Если корень был листом и его удалили
            delete mRoot;
            mRoot = nullptr;
        }
    }

private:
    Node* mRoot;

    struct SplitResult {
        std::string key;
        Node* left;
        Node* right;
    };

    Node* createLeaf(const std::string& key, const std::string& translation) {
        LeafNode* node = new LeafNode(key);
        node->mData.addTranslation(translation);
        return node;
    }

    Node* findLeaf(Node* node, const std::string& key) const {
        if (!node) return nullptr;
        if (node->isLeaf()) return node;
        InternalNode* internal = static_cast<InternalNode*>(node);
        size_t i = 0;
        while (i < internal->mKeys.size() && key >= internal->mKeys[i]) {
            i++;
        }
        return findLeaf(internal->mChildren[i], key);
    }

    SplitResult* insertRecursive(Node* node, const std::string& k,
                                 const std::string& tr) {
        if (node->isLeaf()) {
            LeafNode* leaf = static_cast<LeafNode*>(node);
            if (leaf->mKey == k) {
                leaf->mData.addTranslation(tr);
                return nullptr;
            }
            Node* newLeaf = createLeaf(k, tr);
            SplitResult* res = new SplitResult();
            if (k < leaf->mKey) {
                res->key = leaf->mKey;
                res->left = newLeaf;
                res->right = leaf;
            } else {
                res->key = k;
                res->left = leaf;
                res->right = newLeaf;
            }
            return res;
        }

        InternalNode* internal = static_cast<InternalNode*>(node);
        size_t i = 0;
        while (i < internal->mKeys.size() && k >= internal->mKeys[i]) i++;

        SplitResult* res = insertRecursive(internal->mChildren[i], k, tr);
        if (res) {
            internal->mKeys.insert(internal->mKeys.begin() + i, res->key);
            internal->mChildren[i] = res->left;
            internal->mChildren.insert(internal->mChildren.begin() + i + 1,
                                       res->right);
            delete res;
            if (internal->mKeys.size() > 2) {
                InternalNode* rightNode = new InternalNode();
                std::string midKey = internal->mKeys[1];
                rightNode->mKeys.push_back(internal->mKeys[2]);
                rightNode->mChildren.push_back(internal->mChildren[2]);
                rightNode->mChildren.push_back(internal->mChildren[3]);
                internal->mKeys.resize(1);
                internal->mChildren.resize(2);
                return new SplitResult{midKey, internal, rightNode};
            }
        }
        return nullptr;
    }

    void removeRecursive(Node*& node, const std::string& key, bool& hole) {
        if (node->isLeaf()) {
            LeafNode* leaf = static_cast<LeafNode*>(node);
            if (leaf->mKey == key) hole = true;
            return;
        }

        InternalNode* internal = static_cast<InternalNode*>(node);
        size_t i = 0;
        while (i < internal->mKeys.size() && key >= internal->mKeys[i]) i++;

        bool childHole = false;
        removeRecursive(internal->mChildren[i], key, childHole);

        if (childHole) {
            delete internal->mChildren[i];
            internal->mChildren.erase(internal->mChildren.begin() + i);
            if (i < internal->mKeys.size()) {
                internal->mKeys.erase(internal->mKeys.begin() + i);
            } else if (i > 0) {
                internal->mKeys.erase(internal->mKeys.begin() + i - 1);
            }

            if (internal->mChildren.size() < 2) hole = true;
            else hole = false;
        }
    }

    void destroyTree(Node* node) {
        if (!node) return;
        if (!node->isLeaf()) {
            InternalNode* internal = static_cast<InternalNode*>(node);
            for (Node* child : internal->mChildren) destroyTree(child);
        }
        delete node;
    }
};

#endif
