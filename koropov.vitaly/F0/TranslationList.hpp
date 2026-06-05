#ifndef TRANSLATIONLIST_HPP
#define TRANSLATIONLIST_HPP
#include <string>

struct ListNode
{
  std::string translation;
  ListNode *next;

  ListNode(const std::string &text);
};

class TranslationList
{
private:
  ListNode *head;

public:
  TranslationList();
  ~TranslationList();

  TranslationList(const TranslationList &other);
  TranslationList &operator=(const TranslationList &other);

  void clear();
  void insertSorted(const std::string &translation);
  void print() const;
  bool isEmpty() const;
};

#endif
