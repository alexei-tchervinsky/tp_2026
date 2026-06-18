#include "Geometry.hpp"

#include <algorithm>
#include <cmath>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iterator>
#include <limits>
#include <map>
#include <numeric>
#include <sstream>
#include <stdexcept>
#include <utility>

namespace
{
  struct Line
  {
    std::string text;
  };

  struct ParsedPolygon
  {
    bool valid;
    Polygon polygon;
  };

  std::istream& operator>>(std::istream& input, Line& line)
  {
    return std::getline(input, line.text);
  }

  bool hasOnlySpaces(std::istream& input)
  {
    input >> std::ws;
    return input.eof();
  }

  std::string pointToString(const Point& point)
  {
    std::ostringstream output;
    output << point;
    return output.str();
  }

  ParsedPolygon parsePolygonLine(const Line& line)
  {
    std::istringstream input(line.text);
    Polygon polygon;
    input >> polygon;

    if (!input || !hasOnlySpaces(input))
    {
      return {false, {}};
    }

    std::ostringstream normalized;
    normalized << polygon;

    if (normalized.str() != line.text)
    {
      return {false, {}};
    }

    return {true, std::move(polygon)};
  }

  bool isValidParsedPolygon(const ParsedPolygon& parsed)
  {
    return parsed.valid;
  }

  Polygon extractPolygon(const ParsedPolygon& parsed)
  {
    return parsed.polygon;
  }

  bool hasEvenVertexCount(const Polygon& polygon)
  {
    return polygon.points.size() % 2 == 0;
  }

  bool hasOddVertexCount(const Polygon& polygon)
  {
    return polygon.points.size() % 2 != 0;
  }

  bool hasVertexCount(const Polygon& polygon, std::size_t count)
  {
    return polygon.points.size() == count;
  }

  std::size_t parseVertexCount(const std::string& value)
  {
    std::istringstream input(value);
    long long count = 0;
    input >> count;

    if (!input || !hasOnlySpaces(input) || count < 3)
    {
      throw std::invalid_argument("invalid vertex count");
    }

    return static_cast< std::size_t >(count);
  }

  Polygon parseCommandPolygon(std::istringstream& input)
  {
    Polygon polygon;
    input >> polygon;

    if (!input || !hasOnlySpaces(input))
    {
      throw std::invalid_argument("invalid polygon");
    }

    return polygon;
  }

  double getAreaByPredicate(
      const std::vector< Polygon >& polygons,
      const std::function< bool(const Polygon&) >& predicate)
  {
    return std::accumulate(
        polygons.begin(),
        polygons.end(),
        0.0,
        [&predicate](double result, const Polygon& polygon)
        {
          return predicate(polygon) ? result + getArea(polygon) : result;
        });
  }

  int getMinimumX(const Polygon& polygon)
  {
    return std::min_element(
        polygon.points.begin(),
        polygon.points.end(),
        [](const Point& lhs, const Point& rhs)
        {
          return lhs.x < rhs.x;
        })->x;
  }

  int getMaximumX(const Polygon& polygon)
  {
    return std::max_element(
        polygon.points.begin(),
        polygon.points.end(),
        [](const Point& lhs, const Point& rhs)
        {
          return lhs.x < rhs.x;
        })->x;
  }

  int getMinimumY(const Polygon& polygon)
  {
    return std::min_element(
        polygon.points.begin(),
        polygon.points.end(),
        [](const Point& lhs, const Point& rhs)
        {
          return lhs.y < rhs.y;
        })->y;
  }

  int getMaximumY(const Polygon& polygon)
  {
    return std::max_element(
        polygon.points.begin(),
        polygon.points.end(),
        [](const Point& lhs, const Point& rhs)
        {
          return lhs.y < rhs.y;
        })->y;
  }

  void printArea(double value, std::ostream& output)
  {
    output << std::fixed << std::setprecision(1) << value << '\n';
  }

  void executeArea(
      std::istringstream& input,
      const std::vector< Polygon >& polygons,
      std::ostream& output)
  {
    std::string argument;
    input >> argument;

    if (!input || !hasOnlySpaces(input))
    {
      throw std::invalid_argument("invalid AREA command");
    }

    if (argument == "EVEN")
    {
      printArea(getAreaByPredicate(polygons, hasEvenVertexCount), output);
      return;
    }
    if (argument == "ODD")
    {
      printArea(getAreaByPredicate(polygons, hasOddVertexCount), output);
      return;
    }
    if (argument == "MEAN")
    {
      if (polygons.empty())
      {
        throw std::logic_error("empty collection");
      }

      const double sum = std::accumulate(
          polygons.begin(),
          polygons.end(),
          0.0,
          [](double result, const Polygon& polygon)
          {
            return result + getArea(polygon);
          });

      printArea(sum / static_cast< double >(polygons.size()), output);
      return;
    }

    const std::size_t count = parseVertexCount(argument);
    printArea(
        getAreaByPredicate(
            polygons,
            std::bind(hasVertexCount, std::placeholders::_1, count)),
        output);
  }

  void executeMax(
      std::istringstream& input,
      const std::vector< Polygon >& polygons,
      std::ostream& output)
  {
    std::string argument;
    input >> argument;

    if (!input || !hasOnlySpaces(input) || polygons.empty())
    {
      throw std::invalid_argument("invalid MAX command");
    }

    if (argument == "AREA")
    {
      const auto iterator = std::max_element(
          polygons.begin(),
          polygons.end(),
          [](const Polygon& lhs, const Polygon& rhs)
          {
            return getArea(lhs) < getArea(rhs);
          });
      printArea(getArea(*iterator), output);
      return;
    }

    if (argument == "VERTEXES")
    {
      const auto iterator = std::max_element(
          polygons.begin(),
          polygons.end(),
          [](const Polygon& lhs, const Polygon& rhs)
          {
            return lhs.points.size() < rhs.points.size();
          });
      output << iterator->points.size() << '\n';
      return;
    }

    throw std::invalid_argument("invalid MAX argument");
  }

  void executeMin(
      std::istringstream& input,
      const std::vector< Polygon >& polygons,
      std::ostream& output)
  {
    std::string argument;
    input >> argument;

    if (!input || !hasOnlySpaces(input) || polygons.empty())
    {
      throw std::invalid_argument("invalid MIN command");
    }

    if (argument == "AREA")
    {
      const auto iterator = std::min_element(
          polygons.begin(),
          polygons.end(),
          [](const Polygon& lhs, const Polygon& rhs)
          {
            return getArea(lhs) < getArea(rhs);
          });
      printArea(getArea(*iterator), output);
      return;
    }

    if (argument == "VERTEXES")
    {
      const auto iterator = std::min_element(
          polygons.begin(),
          polygons.end(),
          [](const Polygon& lhs, const Polygon& rhs)
          {
            return lhs.points.size() < rhs.points.size();
          });
      output << iterator->points.size() << '\n';
      return;
    }

    throw std::invalid_argument("invalid MIN argument");
  }

  void executeCount(
      std::istringstream& input,
      const std::vector< Polygon >& polygons,
      std::ostream& output)
  {
    std::string argument;
    input >> argument;

    if (!input || !hasOnlySpaces(input))
    {
      throw std::invalid_argument("invalid COUNT command");
    }

    if (argument == "EVEN")
    {
      output << std::count_if(
          polygons.begin(), polygons.end(), hasEvenVertexCount) << '\n';
      return;
    }

    if (argument == "ODD")
    {
      output << std::count_if(
          polygons.begin(), polygons.end(), hasOddVertexCount) << '\n';
      return;
    }

    const std::size_t count = parseVertexCount(argument);
    output << std::count_if(
        polygons.begin(),
        polygons.end(),
        std::bind(hasVertexCount, std::placeholders::_1, count)) << '\n';
  }

  using CommandHandler = std::function<
      void(
          std::istringstream&,
          std::vector< Polygon >&,
          std::ostream&)>;

  using CommandMap = std::map< std::string, CommandHandler >;

  const CommandMap& getCommandMap()
  {
    static const CommandMap commands{
      {
        "AREA",
        [](std::istringstream& input,
            std::vector< Polygon >& polygons,
            std::ostream& output)
        {
          executeArea(input, polygons, output);
        }
      },
      {
        "MAX",
        [](std::istringstream& input,
            std::vector< Polygon >& polygons,
            std::ostream& output)
        {
          executeMax(input, polygons, output);
        }
      },
      {
        "MIN",
        [](std::istringstream& input,
            std::vector< Polygon >& polygons,
            std::ostream& output)
        {
          executeMin(input, polygons, output);
        }
      },
      {
        "COUNT",
        [](std::istringstream& input,
            std::vector< Polygon >& polygons,
            std::ostream& output)
        {
          executeCount(input, polygons, output);
        }
      },
      {
        "RMECHO",
        [](std::istringstream& input,
            std::vector< Polygon >& polygons,
            std::ostream& output)
        {
          const Polygon polygon = parseCommandPolygon(input);
          output << removeEchoes(polygons, polygon) << '\n';
        }
      },
      {
        "INFRAME",
        [](std::istringstream& input,
            std::vector< Polygon >& polygons,
            std::ostream& output)
        {
          const Polygon polygon = parseCommandPolygon(input);
          output << (isInFrame(polygons, polygon)
              ? "<TRUE>\n"
              : "<FALSE>\n");
        }
      }
    };

    return commands;
  }
}

bool operator==(const Point& lhs, const Point& rhs)
{
  return lhs.x == rhs.x && lhs.y == rhs.y;
}

bool operator!=(const Point& lhs, const Point& rhs)
{
  return !(lhs == rhs);
}

bool operator==(const Polygon& lhs, const Polygon& rhs)
{
  return lhs.points == rhs.points;
}

bool operator!=(const Polygon& lhs, const Polygon& rhs)
{
  return !(lhs == rhs);
}

std::istream& operator>>(std::istream& input, Point& point)
{
  std::istream::sentry sentry(input);
  if (!sentry)
  {
    return input;
  }

  Point temporary{};
  char open = '\0';
  char separator = '\0';
  char close = '\0';

  input >> open >> temporary.x >> separator >> temporary.y >> close;

  if (!input || open != '(' || separator != ';' || close != ')')
  {
    input.setstate(std::ios::failbit);
    return input;
  }

  point = temporary;
  return input;
}

std::ostream& operator<<(std::ostream& output, const Point& point)
{
  return output << '(' << point.x << ';' << point.y << ')';
}

std::istream& operator>>(std::istream& input, Polygon& polygon)
{
  std::istream::sentry sentry(input);
  if (!sentry)
  {
    return input;
  }

  long long count = 0;
  input >> count;

  if (!input || count < 3)
  {
    input.setstate(std::ios::failbit);
    return input;
  }

  std::vector< Point > points(static_cast< std::size_t >(count));
  std::copy_n(
      std::istream_iterator< Point >(input),
      static_cast< std::size_t >(count),
      points.begin());

  if (!input)
  {
    input.setstate(std::ios::failbit);
    return input;
  }

  polygon.points = std::move(points);
  return input;
}

std::ostream& operator<<(std::ostream& output, const Polygon& polygon)
{
  output << polygon.points.size();

  std::vector< std::string > strings(polygon.points.size());
  std::transform(
      polygon.points.begin(),
      polygon.points.end(),
      strings.begin(),
      pointToString);

  if (!strings.empty())
  {
    output << ' ';
    std::copy(
        strings.begin(),
        std::prev(strings.end()),
        std::ostream_iterator< std::string >(output, " "));
    output << strings.back();
  }

  return output;
}

double getArea(const Polygon& polygon)
{
  const auto first = polygon.points.begin();
  const auto last = polygon.points.end();

  const long long sum = std::inner_product(
      first,
      std::prev(last),
      std::next(first),
      0LL,
      std::plus< long long >(),
      [](const Point& lhs, const Point& rhs)
      {
        return static_cast< long long >(lhs.x) * rhs.y -
               static_cast< long long >(lhs.y) * rhs.x;
      });

  const long long closing =
      static_cast< long long >(polygon.points.back().x) * polygon.points.front().y -
      static_cast< long long >(polygon.points.back().y) * polygon.points.front().x;

  return std::abs(static_cast< double >(sum + closing)) / 2.0;
}

std::vector< Polygon > readPolygons(const std::string& filename)
{
  std::ifstream file(filename);
  if (!file)
  {
    throw std::runtime_error("cannot open file");
  }

  const std::vector< Line > lines{
      std::istream_iterator< Line >(file),
      std::istream_iterator< Line >()
  };

  std::vector< ParsedPolygon > parsed(lines.size());
  std::transform(lines.begin(), lines.end(), parsed.begin(), parsePolygonLine);

  std::vector< ParsedPolygon > valid(parsed.size());
  const auto validEnd = std::copy_if(
      parsed.begin(), parsed.end(), valid.begin(), isValidParsedPolygon);
  valid.erase(validEnd, valid.end());

  std::vector< Polygon > polygons(valid.size());
  std::transform(valid.begin(), valid.end(), polygons.begin(), extractPolygon);
  return polygons;
}

std::size_t removeEchoes(
    std::vector< Polygon >& polygons,
    const Polygon& polygon)
{
  const std::size_t oldSize = polygons.size();

  const auto newEnd = std::unique(
      polygons.begin(),
      polygons.end(),
      [&polygon](const Polygon& lhs, const Polygon& rhs)
      {
        return lhs == polygon && rhs == polygon;
      });

  polygons.erase(newEnd, polygons.end());
  return oldSize - polygons.size();
}

bool isInFrame(
    const std::vector< Polygon >& polygons,
    const Polygon& polygon)
{
  if (polygons.empty())
  {
    throw std::logic_error("empty collection");
  }

  const int minimumX = std::accumulate(
      polygons.begin(),
      polygons.end(),
      std::numeric_limits< int >::max(),
      [](int result, const Polygon& current)
      {
        return std::min(result, getMinimumX(current));
      });

  const int maximumX = std::accumulate(
      polygons.begin(),
      polygons.end(),
      std::numeric_limits< int >::min(),
      [](int result, const Polygon& current)
      {
        return std::max(result, getMaximumX(current));
      });

  const int minimumY = std::accumulate(
      polygons.begin(),
      polygons.end(),
      std::numeric_limits< int >::max(),
      [](int result, const Polygon& current)
      {
        return std::min(result, getMinimumY(current));
      });

  const int maximumY = std::accumulate(
      polygons.begin(),
      polygons.end(),
      std::numeric_limits< int >::min(),
      [](int result, const Polygon& current)
      {
        return std::max(result, getMaximumY(current));
      });

  return std::all_of(
      polygon.points.begin(),
      polygon.points.end(),
      [minimumX, maximumX, minimumY, maximumY](const Point& point)
      {
        return point.x >= minimumX && point.x <= maximumX &&
               point.y >= minimumY && point.y <= maximumY;
      });
}

void executeCommand(
    const std::string& command,
    std::vector< Polygon >& polygons,
    std::ostream& output)
{
  try
  {
    std::istringstream input(command);
    std::string name;
    input >> name;

    if (!input)
    {
      throw std::invalid_argument("empty command");
    }

    getCommandMap().at(name)(input, polygons, output);
  }
  catch (const std::exception&)
  {
    output << "<INVALID COMMAND>\n";
  }
}

void processCommands(
    std::istream& input,
    std::vector< Polygon >& polygons,
    std::ostream& output)
{
  std::string command;
  if (std::getline(input, command))
  {
    executeCommand(command, polygons, output);
    processCommands(input, polygons, output);
  }
}
