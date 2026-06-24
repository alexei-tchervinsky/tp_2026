#include "commands.h"
#include "polygon.h"
#include "iofmtguard.hpp"
#include <algorithm>
#include <numeric>
#include <iomanip>
#include <string>
#include <sstream>
#include <stdexcept>
#include <map>
#include <functional>
#include <limits>
#include <iterator>

// ============ ГЛОБАЛЬНАЯ КОЛЛЕКЦИЯ ПОЛИГОНОВ ============
static std::vector< Polygon > g_polys;

void setPolygons(const std::vector< Polygon >& polys)
{
  g_polys = polys;
}

// ============ AREA ============
void cmdArea(std::istream& is, std::ostream& os)
{
  std::string param;
  if (!(is >> param))
  {
    throw std::runtime_error("Missing argument for AREA");
  }

  iofmtguard guard(os);
  os << std::fixed << std::setprecision(1);

  if (param == "EVEN")
  {
    double sum = std::accumulate(g_polys.begin(), g_polys.end(), 0.0,
                                 ConditionalAreaAccumulator(true));
    os << sum << '\n';
  }
  else if (param == "ODD")
  {
    double sum = std::accumulate(g_polys.begin(), g_polys.end(), 0.0,
                                 ConditionalAreaAccumulator(false));
    os << sum << '\n';
  }
  else if (param == "MEAN")
  {
    if (g_polys.empty())
    {
      throw std::runtime_error("Empty dataset for AREA MEAN");
    }
    double sum = std::accumulate(g_polys.begin(), g_polys.end(), 0.0,
                                 AreaAccumulator{});
    os << sum / static_cast< double >(g_polys.size()) << '\n';
  }
  else
  {
    std::size_t n = 0;
    try
    {
      n = std::stoull(param);
    }
    catch (...)
    {
      throw std::runtime_error("Unknown argument for AREA");
    }
    if (n < 3)
    {
      throw std::runtime_error("Vertex count must be >= 3");
    }
    double sum = std::accumulate(g_polys.begin(), g_polys.end(), 0.0,
                                 VertexCountAreaAccumulator(n));
    os << sum << '\n';
  }
}

// ============ MAX ============
void cmdMax(std::istream& is, std::ostream& os)
{
  if (g_polys.empty())
  {
    throw std::runtime_error("Empty collection for MAX");
  }

  std::string param;
  if (!(is >> param))
  {
    throw std::runtime_error("Missing argument for MAX");
  }

  if (param == "AREA")
  {
    auto it = std::max_element(g_polys.begin(), g_polys.end(), AreaLess{});
    iofmtguard guard(os);
    os << std::fixed << std::setprecision(1) << getArea(*it) << '\n';
  }
  else if (param == "VERTEXES")
  {
    auto it = std::max_element(g_polys.begin(), g_polys.end(), VertexCountLess{});
    os << it->points.size() << '\n';
  }
  else
  {
    throw std::runtime_error("Unknown argument for MAX");
  }
}

// ============ MIN ============
void cmdMin(std::istream& is, std::ostream& os)
{
  if (g_polys.empty())
  {
    throw std::runtime_error("Empty collection for MIN");
  }

  std::string param;
  if (!(is >> param))
  {
    throw std::runtime_error("Missing argument for MIN");
  }

  if (param == "AREA")
  {
    auto it = std::min_element(g_polys.begin(), g_polys.end(), AreaLess{});
    iofmtguard guard(os);
    os << std::fixed << std::setprecision(1) << getArea(*it) << '\n';
  }
  else if (param == "VERTEXES")
  {
    auto it = std::min_element(g_polys.begin(), g_polys.end(), VertexCountLess{});
    os << it->points.size() << '\n';
  }
  else
  {
    throw std::runtime_error("Unknown argument for MIN");
  }
}

// ============ COUNT ============
void cmdCount(std::istream& is, std::ostream& os)
{
  std::string param;
  if (!(is >> param))
  {
    throw std::runtime_error("Missing argument for COUNT");
  }

  if (param == "EVEN")
  {
    os << std::count_if(g_polys.begin(), g_polys.end(), EvenVertexPred{}) << '\n';
  }
  else if (param == "ODD")
  {
    os << std::count_if(g_polys.begin(), g_polys.end(), OddVertexPred{}) << '\n';
  }
  else
  {
    std::size_t n = 0;
    try
    {
      n = std::stoull(param);
    }
    catch (...)
    {
      throw std::runtime_error("Unknown argument for COUNT");
    }
    if (n < 3)
    {
      throw std::runtime_error("Vertex count must be >= 3");
    }
    os << std::count_if(g_polys.begin(), g_polys.end(), VertexCountPred(n)) << '\n';
  }
}

// ============ RMECHO ============
struct TargetAndEqual
{
  const Polygon& target;
  explicit TargetAndEqual(const Polygon& t) : target(t) {}
  bool operator()(const Polygon& a, const Polygon& b) const
  {
    return a == target && b == target;
  }
};

void cmdRmEcho(std::istream& is, std::ostream& os)
{
  std::string line;
  if (!std::getline(is, line))
  {
    os << "<INVALID COMMAND>\n";
    return;
  }
  std::istringstream ss(line);
  Polygon target;
  std::string extra;
  if (!(ss >> target) || ss.fail() || (ss >> extra))
  {
    os << "<INVALID COMMAND>\n";
    return;
  }

  std::size_t oldSize = g_polys.size();
  auto newEnd = std::unique(g_polys.begin(), g_polys.end(),
                            TargetAndEqual(target));
  std::size_t newSize = std::distance(g_polys.begin(), newEnd);
  g_polys.erase(newEnd, g_polys.end());
  os << (oldSize - newSize) << '\n';
}

// ============ SAME ============
void cmdSame(std::istream& is, std::ostream& os)
{
  std::string line;
  if (!std::getline(is, line))
  {
    os << "<INVALID COMMAND>\n";
    return;
  }
  std::istringstream ss(line);
  Polygon target;
  std::string extra;
  if (!(ss >> target) || ss.fail() || (ss >> extra))
  {
    os << "<INVALID COMMAND>\n";
    return;
  }

  os << std::count_if(g_polys.begin(), g_polys.end(),
                      SamePred(target)) << '\n';
}

// ============ ДИСПЕТЧЕР КОМАНД ============
void doTasks(const std::vector< Polygon >& polys)
{
  setPolygons(polys);

  std::map< std::string, std::function< void(std::istream&, std::ostream&) > > cmds;
  cmds["AREA"]     = cmdArea;
  cmds["MAX"]      = cmdMax;
  cmds["MIN"]      = cmdMin;
  cmds["COUNT"]    = cmdCount;
  cmds["RMECHO"]   = cmdRmEcho;
  cmds["SAME"]     = cmdSame;

  std::string command;
  while (!(std::cin >> command).eof())
  {
    try
    {
      cmds.at(command)(std::cin, std::cout);
    }
    catch (...)
    {
      std::cout << "<INVALID COMMAND>\n";
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
}
