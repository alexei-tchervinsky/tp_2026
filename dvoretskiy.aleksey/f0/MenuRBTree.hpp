#pragma once

#ifndef MENU_RBTREE_HPP
#define MENU_RBTREE_HPP

#include "RBTree.hpp"

enum class MenuRBTreeOption
{
  Add = 1,
  RemoveWord = 2,
  RemoveTranslation = 3,
  Find = 4,
  LoadCommandFile = 5,
  LoadWordsFile = 6,
  Exit = 7
};

int GetElementConsoleRBTree();

std::string GetWordConsoleRBTree();

bool IsEnglishWord(
  const std::string& word);

bool IsRussianWord(
  const std::string& word);

void PrintTree(
  const Node* node,
  int indent);

void LoadFromFile(
  Node*& root,
  const std::string& fileName);

void LoadWordsFromFile(
  Node*& root,
  const std::string& fileName);

void Menu(RBTree* tree);

#endif
