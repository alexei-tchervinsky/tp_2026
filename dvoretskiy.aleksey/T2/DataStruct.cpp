#include "DataStruct.hpp"

#include <cctype>
#include <iomanip>
#include <istream>
#include <ostream>
#include <sstream>
#include <string>

namespace
{
  struct DelimiterIO
  {
    char expected;
  };

  struct CharLiteralIO
  {
    char& value;
  };

  struct HexLiteralIO
  {
    unsigned long long& value;
  };

  struct StringIO
  {
    std::string& value;
  };

  std::istream& operator>>(std::istream& input, DelimiterIO&& delimiter)
  {
    std::istream::sentry sentry(input);
    if (!sentry)
    {
      return input;
    }

    char current = '\0';
    input >> current;
    if (input && current != delimiter.expected)
    {
      input.setstate(std::ios::failbit);
    }
    return input;
  }

  std::istream& operator>>(std::istream& input, CharLiteralIO&& literal)
  {
    std::istream::sentry sentry(input);
    if (!sentry)
    {
      return input;
    }

    char quoteBegin = '\0';
    char value = '\0';
    char quoteEnd = '\0';
    input >> quoteBegin >> value >> quoteEnd;

    if (!input || quoteBegin != '\'' || quoteEnd != '\'')
    {
      input.setstate(std::ios::failbit);
      return input;
    }

    literal.value = value;
    return input;
  }

  std::istream& operator>>(std::istream& input, HexLiteralIO&& literal)
  {
    std::istream::sentry sentry(input);
    if (!sentry)
    {
      return input;
    }

    std::string token;
    char current = '\0';

    while (input.get(current))
    {
      if (current == ':')
      {
        input.unget();
        break;
      }
      token += current;
    }

    if (token.size() < 3 || token[0] != '0' ||
        (token[1] != 'x' && token[1] != 'X'))
    {
      input.setstate(std::ios::failbit);
      return input;
    }

    for (std::size_t i = 2; i < token.size(); i++)
    {
      const unsigned char symbol = static_cast<unsigned char>(token[i]);
      if (!std::isxdigit(symbol))
      {
        input.setstate(std::ios::failbit);
        return input;
      }
    }

    std::istringstream converter(token.substr(2));
    unsigned long long value = 0;
    converter >> std::hex >> value;

    if (!converter || converter.peek() != std::char_traits<char>::eof())
    {
      input.setstate(std::ios::failbit);
      return input;
    }

    literal.value = value;
    return input;
  }

  std::istream& operator>>(std::istream& input, StringIO&& string)
  {
    std::istream::sentry sentry(input);
    if (!sentry)
    {
      return input;
    }

    return input >> std::quoted(string.value);
  }
}

std::istream& operator>>(std::istream& input, DataStruct& data)
{
  std::istream::sentry sentry(input);
  if (!sentry)
  {
    return input;
  }

  DataStruct temporary{};
  bool key1Read = false;
  bool key2Read = false;
  bool key3Read = false;

  input >> DelimiterIO{'('} >> DelimiterIO{':'};

  for (int i = 0; i < 3 && input; i++)
  {
    std::string key;
    input >> key;

    if (key == "key1")
    {
      if (key1Read)
      {
        input.setstate(std::ios::failbit);
        break;
      }
      input >> CharLiteralIO{temporary.key1};
      key1Read = true;
    }
    else if (key == "key2")
    {
      if (key2Read)
      {
        input.setstate(std::ios::failbit);
        break;
      }
      input >> HexLiteralIO{temporary.key2};
      key2Read = true;
    }
    else if (key == "key3")
    {
      if (key3Read)
      {
        input.setstate(std::ios::failbit);
        break;
      }
      input >> StringIO{temporary.key3};
      key3Read = true;
    }
    else
    {
      input.setstate(std::ios::failbit);
      break;
    }

    input >> DelimiterIO{':'};
  }

  input >> DelimiterIO{')'};

  if (input && key1Read && key2Read && key3Read)
  {
    data = temporary;
  }
  else
  {
    input.setstate(std::ios::failbit);
  }

  return input;
}

std::ostream& operator<<(std::ostream& output, const DataStruct& data)
{
  const std::ios::fmtflags flags = output.flags();

  output << "(:key1 '" << data.key1
         << "':key2 0x"
         << std::uppercase << std::hex << data.key2
         << ":key3 " << std::quoted(data.key3)
         << ":)";

  output.flags(flags);
  return output;
}

bool DataStructComparator::operator()(
    const DataStruct& lhs,
    const DataStruct& rhs) const
{
  if (lhs.key1 != rhs.key1)
  {
    return lhs.key1 < rhs.key1;
  }
  if (lhs.key2 != rhs.key2)
  {
    return lhs.key2 < rhs.key2;
  }
  return lhs.key3.size() < rhs.key3.size();
}
