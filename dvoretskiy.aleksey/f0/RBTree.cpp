#include "RBTree.hpp"

#include <algorithm>

namespace
{
  void SetNodeColor(Node* node, const Color color)
  {
    if (node != nullptr)
    {
      node->NodeColor = color;
    }
  }

  void RotateLeft(Node*& root, Node* node)
  {
    if (node == nullptr || node->Right == nullptr)
    {
      return;
    }

    Node* rightChild = node->Right;

    node->Right = rightChild->Left;

    if (rightChild->Left != nullptr)
    {
      rightChild->Left->Parent = node;
    }

    rightChild->Parent = node->Parent;

    if (node->Parent == nullptr)
    {
      root = rightChild;
    }
    else if (node == node->Parent->Left)
    {
      node->Parent->Left = rightChild;
    }
    else
    {
      node->Parent->Right = rightChild;
    }

    rightChild->Left = node;
    node->Parent = rightChild;
  }

  void RotateRight(Node*& root, Node* node)
  {
    if (node == nullptr || node->Left == nullptr)
    {
      return;
    }

    Node* leftChild = node->Left;

    node->Left = leftChild->Right;

    if (leftChild->Right != nullptr)
    {
      leftChild->Right->Parent = node;
    }

    leftChild->Parent = node->Parent;

    if (node->Parent == nullptr)
    {
      root = leftChild;
    }
    else if (node == node->Parent->Left)
    {
      node->Parent->Left = leftChild;
    }
    else
    {
      node->Parent->Right = leftChild;
    }

    leftChild->Right = node;
    node->Parent = leftChild;
  }

  void FixInsert(Node*& root, Node* node)
  {
    while (node != root &&
      GetColor(node->Parent) == Color::Red)
    {
      Node* parent = node->Parent;
      Node* grandParent = parent->Parent;

      if (parent == grandParent->Left)
      {
        Node* uncle = grandParent->Right;

        if (GetColor(uncle) == Color::Red)
        {
          SetNodeColor(parent, Color::Black);
          SetNodeColor(uncle, Color::Black);
          SetNodeColor(grandParent, Color::Red);

          node = grandParent;
        }
        else
        {
          if (node == parent->Right)
          {
            node = parent;
            RotateLeft(root, node);

            parent = node->Parent;
            grandParent = parent->Parent;
          }

          SetNodeColor(parent, Color::Black);
          SetNodeColor(grandParent, Color::Red);

          RotateRight(root, grandParent);
        }
      }
      else
      {
        Node* uncle = grandParent->Left;

        if (GetColor(uncle) == Color::Red)
        {
          SetNodeColor(parent, Color::Black);
          SetNodeColor(uncle, Color::Black);
          SetNodeColor(grandParent, Color::Red);

          node = grandParent;
        }
        else
        {
          if (node == parent->Left)
          {
            node = parent;
            RotateRight(root, node);

            parent = node->Parent;
            grandParent = parent->Parent;
          }

          SetNodeColor(parent, Color::Black);
          SetNodeColor(grandParent, Color::Red);

          RotateLeft(root, grandParent);
        }
      }
    }

    SetNodeColor(root, Color::Black);
  }

  void Transplant(
    Node*& root,
    Node* oldNode,
    Node* newNode)
  {
    if (oldNode->Parent == nullptr)
    {
      root = newNode;
    }
    else if (oldNode == oldNode->Parent->Left)
    {
      oldNode->Parent->Left = newNode;
    }
    else
    {
      oldNode->Parent->Right = newNode;
    }

    if (newNode != nullptr)
    {
      newNode->Parent = oldNode->Parent;
    }
  }

  void FixDelete(Node*& root, Node* node)
  {
    while (node != root &&
      GetColor(node) == Color::Black)
    {
      Node* parent = node->Parent;

      if (node == parent->Left)
      {
        Node* sibling = parent->Right;

        if (GetColor(sibling) == Color::Red)
        {
          SetNodeColor(sibling, Color::Black);
          SetNodeColor(parent, Color::Red);

          RotateLeft(root, parent);

          sibling = parent->Right;
        }

        const Color leftColor =
          GetColor(
            sibling == nullptr
            ? nullptr
            : sibling->Left);

        const Color rightColor =
          GetColor(
            sibling == nullptr
            ? nullptr
            : sibling->Right);

        if (leftColor == Color::Black &&
          rightColor == Color::Black)
        {
          SetNodeColor(sibling, Color::Red);
          node = parent;
        }
        else
        {
          if (rightColor == Color::Black)
          {
            SetNodeColor(
              sibling == nullptr
              ? nullptr
              : sibling->Left,
              Color::Black);

            SetNodeColor(sibling, Color::Red);

            RotateRight(root, sibling);

            sibling = parent->Right;
          }

          SetNodeColor(
            sibling,
            GetColor(parent));

          SetNodeColor(parent, Color::Black);

          SetNodeColor(
            sibling == nullptr
            ? nullptr
            : sibling->Right,
            Color::Black);

          RotateLeft(root, parent);

          node = root;
        }
      }
      else
      {
        Node* sibling = parent->Left;

        if (GetColor(sibling) == Color::Red)
        {
          SetNodeColor(sibling, Color::Black);
          SetNodeColor(parent, Color::Red);

          RotateRight(root, parent);

          sibling = parent->Left;
        }

        const Color leftColor =
          GetColor(
            sibling == nullptr
            ? nullptr
            : sibling->Left);

        const Color rightColor =
          GetColor(
            sibling == nullptr
            ? nullptr
            : sibling->Right);

        if (leftColor == Color::Black &&
          rightColor == Color::Black)
        {
          SetNodeColor(sibling, Color::Red);
          node = parent;
        }
        else
        {
          if (leftColor == Color::Black)
          {
            SetNodeColor(
              sibling == nullptr
              ? nullptr
              : sibling->Right,
              Color::Black);

            SetNodeColor(sibling, Color::Red);

            RotateLeft(root, sibling);

            sibling = parent->Left;
          }

          SetNodeColor(
            sibling,
            GetColor(parent));

          SetNodeColor(parent, Color::Black);

          SetNodeColor(
            sibling == nullptr
            ? nullptr
            : sibling->Left,
            Color::Black);

          RotateRight(root, parent);

          node = root;
        }
      }
    }

    SetNodeColor(node, Color::Black);
  }
}

Color GetColor(const Node* node)
{
  if (node == nullptr)
  {
    return Color::Black;
  }

  return node->NodeColor;
}

Node* Find(
  Node* node,
  const std::string& word)
{
  while (node != nullptr)
  {
    if (word == node->EnglishWord)
    {
      return node;
    }

    if (word < node->EnglishWord)
    {
      node = node->Left;
    }
    else
    {
      node = node->Right;
    }
  }

  return nullptr;
}

Node* MinValueNode(Node* node)
{
  if (node == nullptr)
  {
    return nullptr;
  }

  while (node->Left != nullptr)
  {
    node = node->Left;
  }

  return node;
}

void InsertValue(
  Node*& root,
  const std::string& word,
  const std::string& translation)
{
  Node* existing = Find(root, word);

  if (existing != nullptr)
  {
    const auto translationIterator =
      std::find(
        existing->Translations->cbegin(),
        existing->Translations->cend(),
        translation);

    if (translationIterator ==
      existing->Translations->cend())
    {
      existing->Translations->push_back(
        translation);

      existing->Translations->sort();
    }

    return;
  }

  Node* node = new Node;

  node->EnglishWord = word;
  node->Translations =
    new std::list<std::string>;

  node->Translations->push_back(translation);

  Node* parent = nullptr;
  Node* current = root;

  while (current != nullptr)
  {
    parent = current;

    if (word < current->EnglishWord)
    {
      current = current->Left;
    }
    else
    {
      current = current->Right;
    }
  }

  node->Parent = parent;

  if (parent == nullptr)
  {
    root = node;
  }
  else if (word < parent->EnglishWord)
  {
    parent->Left = node;
  }
  else
  {
    parent->Right = node;
  }

  FixInsert(root, node);
}

bool DeleteValue(
  Node*& root,
  const std::string& word)
{
  Node* target = Find(root, word);

  if (target == nullptr)
  {
    return false;
  }

  Node* replacement = target;
  Color removedColor = replacement->NodeColor;

  Node* child = nullptr;
  Node* childParent = nullptr;

  bool childIsLeft = false;

  if (target->Left == nullptr)
  {
    child = target->Right;
    childParent = target->Parent;

    if (childParent != nullptr)
    {
      childIsLeft =
        target == childParent->Left;
    }

    Transplant(root, target, target->Right);
  }
  else if (target->Right == nullptr)
  {
    child = target->Left;
    childParent = target->Parent;

    if (childParent != nullptr)
    {
      childIsLeft =
        target == childParent->Left;
    }

    Transplant(root, target, target->Left);
  }
  else
  {
    replacement =
      MinValueNode(target->Right);

    removedColor =
      replacement->NodeColor;

    child = replacement->Right;

    if (replacement->Parent == target)
    {
      childParent = replacement;
      childIsLeft = false;

      if (child != nullptr)
      {
        child->Parent = replacement;
      }
    }
    else
    {
      childParent = replacement->Parent;
      childIsLeft = true;

      Transplant(
        root,
        replacement,
        replacement->Right);

      replacement->Right = target->Right;
      replacement->Right->Parent =
        replacement;
    }

    Transplant(root, target, replacement);

    replacement->Left = target->Left;
    replacement->Left->Parent = replacement;

    replacement->NodeColor =
      target->NodeColor;
  }

  delete target->Translations;
  delete target;

  if (removedColor == Color::Black)
  {
    if (child != nullptr)
    {
      FixDelete(root, child);
    }
    else if (childParent != nullptr)
    {
      Node temporaryNode;

      temporaryNode.NodeColor =
        Color::Black;

      temporaryNode.Parent =
        childParent;

      if (childIsLeft)
      {
        childParent->Left =
          &temporaryNode;
      }
      else
      {
        childParent->Right =
          &temporaryNode;
      }

      FixDelete(root, &temporaryNode);

      if (temporaryNode.Parent != nullptr)
      {
        if (temporaryNode.Parent->Left ==
          &temporaryNode)
        {
          temporaryNode.Parent->Left =
            nullptr;
        }

        if (temporaryNode.Parent->Right ==
          &temporaryNode)
        {
          temporaryNode.Parent->Right =
            nullptr;
        }
      }
    }
  }

  SetNodeColor(root, Color::Black);

  return true;
}

bool DeleteTranslation(
  Node*& root,
  const std::string& word,
  const std::string& translation)
{
  Node* node = Find(root, word);

  if (node == nullptr)
  {
    return false;
  }

  const auto translationIterator =
    std::find(
      node->Translations->begin(),
      node->Translations->end(),
      translation);

  if (translationIterator ==
    node->Translations->end())
  {
    return false;
  }

  node->Translations->erase(
    translationIterator);

  if (node->Translations->empty())
  {
    DeleteValue(root, word);
  }

  return true;
}

void FreeTree(Node*& node)
{
  if (node == nullptr)
  {
    return;
  }

  FreeTree(node->Left);
  FreeTree(node->Right);

  delete node->Translations;
  delete node;

  node = nullptr;
}
