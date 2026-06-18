#ifndef ANALYTICS_HPP
#define ANALYTICS_HPP
#include <string>
#include <unordered_map>
class Analytics
{
public:
  void printTop3(const std::unordered_map<std::string, int> &table) const;
};
#endif
