#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <numeric>
#include <iomanip>
#include <iterator>
#include "Polygon.hpp"

// Реализация AREA разновидностей
void handleArea(const std::vector<Polygon> &polygons, std::istream &is)
{
  std::string arg;
  is >> arg;

  double totalArea = 0.0;
  size_t count = 0;

  if (arg == "EVEN")
  {
    totalArea = std::accumulate(polygons.begin(),
                                polygons.end(), 0.0,
                                [](double sum, const Polygon &p)
                                {
                                  return sum + (p.points.size() % 2 == 0 ? getArea(p) : 0.0);
                                });
  }
  else if (arg == "ODD")
  {
    totalArea = std::accumulate(polygons.begin(),
                                polygons.end(), 0.0,
                                [](double sum, const Polygon &p)
                                {
                                  return sum + (p.points.size() % 2 != 0 ? getArea(p) : 0.0);
                                });
  }
  else if (arg == "MEAN")
  {
    if (polygons.empty())
    {
      std::cout << "<INVALID COMMAND>\n";
      return;
    }
    totalArea = std::accumulate(polygons.begin(),
                                polygons.end(), 0.0,
                                [](double sum, const Polygon &p)
                                {
                                  return sum + getArea(p);
                                });
    totalArea /= polygons.size();
  }
  else
  {
    // Случай, когда передано конкретное число вершин
    try
    {
      size_t numVertexes = std::stoull(arg);
      if (numVertexes < 3)
        throw std::invalid_argument("");
      totalArea = std::accumulate(polygons.begin(),
                                  polygons.end(), 0.0,
                                  [numVertexes](double sum, const Polygon &p)
                                  {
                                    return sum + (p.points.size() == numVertexes ? getArea(p) : 0.0);
                                  });
    }
    catch (...)
    {
      std::cout << "<INVALID COMMAND>\n";
      return;
    }
  }
  std::cout << std::fixed << std::setprecision(1) << totalArea << "\n";
}
// Реализация MAX
void handleMax(const std::vector<Polygon> &polygons, std::istream &is)
{
  if (polygons.empty())
  {
    std::cout << "<INVALID COMMAND>\n";
    return;
  }
  std::string arg;
  is >> arg;
  if (arg == "AREA")
  {
    auto it = std::max_element(polygons.begin(),
                               polygons.end(), [](const Polygon &a, const Polygon &b)
                               { return getArea(a) < getArea(b); });
    std::cout << std::fixed << std::setprecision(1) << getArea(*it) << "\n";
  }
  else if (arg == "VERTEXES")
  {
    auto it = std::max_element(polygons.begin(),
                               polygons.end(), [](const Polygon &a, const Polygon &b)
                               { return a.points.size() < b.points.size(); });
    std::cout << it->points.size() << "\n";
  }
  else
  {
    std::cout << "<INVALID COMMAND>\n";
  }
}
void handleMin(const std::vector<Polygon> &polygons, std::istream &is)
{
  if (polygons.empty())
  {
    std::cout << "<INVALID COMMAND>\n";
    return;
  }
  std::string arg;
  is >> arg;
  if (arg == "AREA")
  {
    auto it = std::min_element(polygons.begin(),
                               polygons.end(), [](const Polygon &a, const Polygon &b)
                               { return getArea(a) < getArea(b); });
    std::cout << std::fixed << std::setprecision(1) << getArea(*it) << "\n";
  }
  else if (arg == "VERTEXES")
  {
    auto it = std::min_element(polygons.begin(),
                               polygons.end(), [](const Polygon &a, const Polygon &b)
                               { return a.points.size() < b.points.size(); });
    std::cout << it->points.size() << "\n";
  }
  else
  {
    std::cout << "<INVALID COMMAND>\n";
  }
}
void handleCount(const std::vector<Polygon> &polygons, std::istream &is)
{
  std::string arg;
  is >> arg;
  long long count = 0;
  if (arg == "EVEN")
  {
    count = std::count_if(polygons.begin(),
                          polygons.end(), [](const Polygon &p)
                          { return p.points.size() % 2 == 0; });
  }
  else if (arg == "ODD")
  {
    count = std::count_if(polygons.begin(),
                          polygons.end(), [](const Polygon &p)
                          { return p.points.size() % 2 != 0; });
  }
  else
  {
    try
    {
      size_t numVertexes = std::stoull(arg);
      count = std::count_if(polygons.begin(),
                            polygons.end(), [numVertexes](const Polygon &p)
                            { return p.points.size() == numVertexes; });
    }
    catch (...)
    {
      std::cout << "<INVALID COMMAND>\n";
      return;
    }
  }
  std::cout << count << "\n";
}
void handleEcho(std::vector<Polygon> &polygons, std::istream &is)
{
  Polygon target;
  if (!(is >> target))
  {
    std::cout << "<INVALID COMMAND>\n";
    return;
  }
  std::vector<Polygon> updatedCollection;
  updatedCollection.reserve(polygons.size() * 2);
  size_t addedCount = 0;
  std::for_each(polygons.begin(),
                polygons.end(), [&](const Polygon &p)
                {
  updatedCollection.push_back(p);
  if (isPolygonEqual(p, target))
  {
  updatedCollection.push_back(p);
  addedCount++;
  } });
  polygons = std::move(updatedCollection);
  std::cout << addedCount << "\n";
}
void handleInFrame(const std::vector<Polygon> &polygons, std::istream &is)
{
  Polygon target;
  if (!(is >> target) || polygons.empty())
  {
    std::cout << "<INVALID COMMAND>\n";
    return;
  }

  Frame currentFrame = getCollectionFrame(polygons);
  if (isPolygonInFrame(target, currentFrame))
  {
    std::cout << "<TRUE>\n";
  }
  else
  {
    std::cout << "<FALSE>\n";
  }
}

int main(int argc, char *argv[])
{
  if (argc != 2)
  {
    std::cerr << "Error: filename parameter is missing.\n";
    return 1;
  }
  std::ifstream file(argv[1]);
  if (!file.is_open())
  {
    std::cerr << "Error: cannot open file.\n";
    return 1;
  }
  std::vector<Polygon> polygons;
  std::string line;
  while (std::getline(file, line))
  {
    if (line.empty())
      continue;
    std::stringstream ss(line);
    Polygon poly;
    if (ss >> poly)
    {
      polygons.push_back(poly);
    }
  }
  file.close();
  std::string command;
  while (std::cin >> command)
  {
    if (command == "AREA")
    {
      handleArea(polygons, std::cin);
    }
    else if (command == "MAX")
    {
      handleMax(polygons, std::cin);
    }
    else if (command == "MIN")
    {
      handleMin(polygons, std::cin);
    }
    else if (command == "COUNT")
    {
      handleCount(polygons, std::cin);
    }
    else if (command == "ECHO")
    {
      handleEcho(polygons, std::cin);
    }
    else if (command == "INFRAME")
    {
      handleInFrame(polygons, std::cin);
    }
    else
    {
      std::cout << "<INVALID COMMAND>\n";
      std::string dummy;
      std::getline(std::cin, dummy);
    }
  }

  return 0;
}
