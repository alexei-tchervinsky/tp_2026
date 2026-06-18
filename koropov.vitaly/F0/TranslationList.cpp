#include "TranslationList.hpp"
#include <iostream>
#include <stdexcept>

ListNode::ListNode(const std::string &text) : translation(text), next(nullptr) {}

TranslationList::TranslationList() : head(nullptr) {}

TranslationList::~TranslationList()
{
  clear();
}

TranslationList::TranslationList(const TranslationList &other) : head(nullptr)
{
  ListNode *current = other.head;
  ListNode *tail = nullptr;
  while (current != nullptr)
  {
    ListNode *newNode = new ListNode(current->translation);
    if (head == nullptr)
    {
      head = newNode;
    }
    else
    {
      tail->next = newNode;
    }
    tail = newNode;
    current = current->next;
  }
}

TranslationList &TranslationList::operator=(const TranslationList &other)
{
  if (this != &other)
  {
    clear();
    ListNode *current = other.head;
    ListNode *tail = nullptr;
    while (current != nullptr)
    {
      ListNode *newNode = new ListNode(current->translation);
      if (head == nullptr)
      {
        head = newNode;
      }
      else
      {
        tail->next = newNode;
      }
      tail = newNode;
      current = current->next;
    }
  }
  return *this;
}

void TranslationList::clear()
{
  ListNode *current = head;
  while (current != nullptr)
  {
    ListNode *nextNode = current->next;
    delete current;
    current = nextNode;
  }
  head = nullptr;
}

void TranslationList::insertSorted(const std::string &translation)
{
  if (translation.empty())
  {
    throw std::invalid_argument("Error: Translation cannot be empty.");
  }

  ListNode *newNode = new ListNode(translation);

  if (head == nullptr || head->translation > translation)
  {
    newNode->next = head;
    head = newNode;
    return;
  }

  if (head->translation == translation)
  {
    delete newNode;
    return;
  }

  ListNode *current = head;
  while (current->next != nullptr && current->next->translation < translation)
  {
    current = current->next;
  }

  if (current->next != nullptr && current->next->translation == translation)
  {
    delete newNode;
    return;
  }

  newNode->next = current->next;
  current->next = newNode;
}

void TranslationList::print() const
{
  ListNode *current = head;
  if (current == nullptr)
  {
    std::cout << "[No translations]";
    return;
  }
  while (current != nullptr)
  {
    std::cout << current->translation;
    if (current->next != nullptr)
    {
      std::cout << ", ";
    }
    current = current->next;
  }
}

bool TranslationList::isEmpty() const
{
  return head == nullptr;
}
