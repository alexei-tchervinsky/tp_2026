#include <algorithm>
#include <cctype>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

struct DataStruct
{
  unsigned long long key1;
  char key2;
  std::string key3;
};

std::string trim(const std::string& s)
{
  std::size_t start = 0;
  while (start < s.size() && std::isspace(static_cast<unsigned char>(s[start])))
  {
    ++start;
  }

  std::size_t end = s.size();
  while (end > start && std::isspace(static_cast<unsigned char>(s[end - 1])))
  {
    --end;
  }

  return s.substr(start, end - start);
}

bool isULLLit(const std::string& s)
{
  std::string str = trim(s);
  if (str.size() < 4)
  {
    return false;
  }

  std::string suffix = str.substr(str.size() - 3);
  if (!(suffix == "ull" || suffix == "ULL"))
  {
    return false;
  }

  for (std::size_t i = 0; i < str.size() - 3; ++i)
  {
    if (!std::isdigit(static_cast<unsigned char>(str[i])))
    {
      return false;
    }
  }

  return true;
}

bool isCharLit(const std::string& s)
{
  std::string str = trim(s);
  return str.size() == 3 && str.front() == '\'' && str.back() == '\'';
}

std::istream& operator>>(std::istream& in, DataStruct& dest)
{
  std::string line;
  if (!std::getline(in, line))
  {
    return in;
  }

  line = trim(line);
  if (line.empty())
  {
    in.setstate(std::ios::failbit);
    return in;
  }

  if (line.size() < 4 || line.substr(0, 2) != "(:" || line.substr(line.size() - 2) != ":)")
  {
    in.setstate(std::ios::failbit);
    return in;
  }

  bool hasKey1 = false;
  bool hasKey2 = false;
  bool hasKey3 = false;

  unsigned long long key1 = 0;
  char key2 = '\0';
  std::string key3;

  std::size_t pos1 = line.find(":key1 ");
  if (pos1 != std::string::npos)
  {
    std::size_t start = pos1 + 6;
    std::size_t end = line.find(':', start);
    if (end != std::string::npos)
    {
      std::string token = trim(line.substr(start, end - start));
      if (isULLLit(token))
      {
        key1 = std::stoull(token.substr(0, token.size() - 3));
        hasKey1 = true;
      }
    }
  }

  std::size_t pos2 = line.find(":key2 ");
  if (pos2 != std::string::npos)
  {
    std::size_t start = pos2 + 6;
    std::size_t end = line.find(':', start);
    if (end != std::string::npos)
    {
      std::string token = trim(line.substr(start, end - start));
      if (isCharLit(token))
      {
        key2 = token[1];
        hasKey2 = true;
      }
    }
  }

  std::size_t pos3 = line.find(":key3 ");
  if (pos3 != std::string::npos)
  {
    std::size_t firstQuote = line.find('"', pos3 + 6);
    if (firstQuote != std::string::npos)
    {
      std::size_t secondQuote = line.find('"', firstQuote + 1);
      if (secondQuote != std::string::npos)
      {
        key3 = line.substr(firstQuote + 1, secondQuote - firstQuote - 1);
        hasKey3 = true;
      }
    }
  }

  if (!hasKey1 || !hasKey2 || !hasKey3)
  {
    in.setstate(std::ios::failbit);
    return in;
  }

  dest.key1 = key1;
  dest.key2 = key2;
  dest.key3 = key3;
  return in;
}

std::ostream& operator<<(std::ostream& out, const DataStruct& src)
{
  out << "(:key1 " << src.key1 << "ull";
  out << ":key2 '" << src.key2 << "'";
  out << ":key3 \"" << src.key3 << "\":)";
  return out;
}

bool compare(const DataStruct& a, const DataStruct& b)
{
  if (a.key1 != b.key1)
  {
    return a.key1 < b.key1;
  }
  if (a.key2 != b.key2)
  {
    return a.key2 < b.key2;
  }
  return a.key3.length() < b.key3.length();
}

int main()
{
  std::vector< DataStruct > data;
  std::string line;

  while (std::getline(std::cin, line))
  {
    if (trim(line).empty())
    {
      continue;
    }

    std::istringstream iss(line);
    DataStruct temp;
    if (iss >> temp)
    {
      data.push_back(temp);
    }
  }

  std::sort(data.begin(), data.end(), compare);

  std::copy(
    data.begin(),
    data.end(),
    std::ostream_iterator< DataStruct >(std::cout, "\n")
  );

  return 0;
}
