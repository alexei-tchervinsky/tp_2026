#pragma once

#ifndef RBTREE_HPP
#define RBTREE_HPP

#include <list>
#include <string>

enum class Color
{
  Red,
  Black
};

struct Node
{
  std::string EnglishWord;
  std::list<std::string>* Translations = nullptr;

  Color NodeColor = Color::Red;

  Node* Left = nullptr;
  Node* Right = nullptr;
  Node* Parent = nullptr;
};

struct RBTree
{
  Node* Root = nullptr;
};

Color GetColor(const Node* node);

Node* Find(Node* node, const std::string& word);
Node* MinValueNode(Node* node);

void InsertValue(
  Node*& root,
  const std::string& word,
  const std::string& translation);

bool DeleteValue(
  Node*& root,
  const std::string& word);

bool DeleteTranslation(
  Node*& root,
  const std::string& word,
  const std::string& translation);

void FreeTree(Node*& node);

#endif
