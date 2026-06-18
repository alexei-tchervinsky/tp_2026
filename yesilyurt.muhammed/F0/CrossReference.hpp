#ifndef CROSS_REFERENCE_HPP
#define CROSS_REFERENCE_HPP

#include <iosfwd>
#include <map>
#include <set>
#include <string>

class CrossReference
{
public:
  void clear();

  void addWord(const std::string& word, int lineNumber);
  bool contains(const std::string& word) const;
  void removeWord(const std::string& word);

  void printWord(const std::string& word, std::ostream& out) const;
  void printAll(std::ostream& out) const;

  bool loadFromFile(const std::string& fileName, std::ostream& numberedTextOut);

private:
  std::map< std::string, std::set< int > > dictionary_;

  static std::string normalizeWord(const std::string& word);
  void insertWordsFromLine(const std::string& line, int lineNumber);
};

#endif
