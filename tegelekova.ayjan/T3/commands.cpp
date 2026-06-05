#include "commands.hpp"
#include "stream_guard.hpp"
#include <iostream>
#include <algorithm>
#include <numeric>
#include <iterator>
#include <sstream>
#include <iomanip>
#include <cmath>

namespace tchervinsky
{
  static void printDouble(double value)
  {
    StreamGuard guard(std::cout);
    std::cout << std::fixed << std::setprecision(1) << value << std::endl;
  }

  void areaEven(const std::vector<Polygon>& polygons)
  {
    std::vector<double> areas;
    std::copy_if(polygons.begin(), polygons.end(), std::back_inserter(areas),
      [](const Polygon& p) { return p.points.size() % 2 == 0; });
    
    double sum = std::accumulate(areas.begin(), areas.end(), 0.0,
      [](double acc, const Polygon& p) { return acc + getArea(p); });
    
    printDouble(sum);
  }

  void areaOdd(const std::vector<Polygon>& polygons)
  {
    std::vector<double> areas;
    std::copy_if(polygons.begin(), polygons.end(), std::back_inserter(areas),
      [](const Polygon& p) { return p.points.size() % 2 == 1; });
    
    double sum = std::accumulate(areas.begin(), areas.end(), 0.0,
      [](double acc, const Polygon& p) { return acc + getArea(p); });
    
    printDouble(sum);
  }

  void areaMean(const std::vector<Polygon>& polygons)
  {
    if (polygons.empty())
    {
      std::cout << "<INVALID COMMAND>" << std::endl;
      return;
    }
    
    double sum = std::accumulate(polygons.begin(), polygons.end(), 0.0,
      [](double acc, const Polygon& p) { return acc + getArea(p); });
    
    printDouble(sum / polygons.size());
  }

  void areaVertex(const std::vector<Polygon>& polygons, size_t vertexCount)
  {
    if (vertexCount < 3)
    {
      std::cout << "<INVALID COMMAND>" << std::endl;
      return;
    }
    
    std::vector<double> areas;
    std::copy_if(polygons.begin(), polygons.end(), std::back_inserter(areas),
      [vertexCount](const Polygon& p) { return p.points.size() == vertexCount; });
    
    double sum = std::accumulate(areas.begin(), areas.end(), 0.0,
      [](double acc, const Polygon& p) { return acc + getArea(p); });
    
    printDouble(sum);
  }

  void maxArea(const std::vector<Polygon>& polygons)
  {
    if (polygons.empty())
    {
      std::cout << "<INVALID COMMAND>" << std::endl;
      return;
    }
    
    auto it = std::max_element(polygons.begin(), polygons.end(),
      [](const Polygon& a, const Polygon& b) { return getArea(a) < getArea(b); });
    
    printDouble(getArea(*it));
  }

  void maxVertexes(const std::vector<Polygon>& polygons)
  {
    if (polygons.empty())
    {
      std::cout << "<INVALID COMMAND>" << std::endl;
      return;
    }
    
    auto it = std::max_element(polygons.begin(), polygons.end(),
      [](const Polygon& a, const Polygon& b) { return a.points.size() < b.points.size(); });
    
    std::cout << it->points.size() << std::endl;
  }

  void minArea(const std::vector<Polygon>& polygons)
  {
    if (polygons.empty())
    {
      std::cout << "<INVALID COMMAND>" << std::endl;
      return;
    }
    
    auto it = std::min_element(polygons.begin(), polygons.end(),
      [](const Polygon& a, const Polygon& b) { return getArea(a) < getArea(b); });
    
    printDouble(getArea(*it));
  }

  void minVertexes(const std::vector<Polygon>& polygons)
  {
    if (polygons.empty())
    {
      std::cout << "<INVALID COMMAND>" << std::endl;
      return;
    }
    
    auto it = std::min_element(polygons.begin(), polygons.end(),
      [](const Polygon& a, const Polygon& b) { return a.points.size() < b.points.size(); });
    
    std::cout << it->points.size() << std::endl;
  }

  void countEven(const std::vector<Polygon>& polygons)
  {
    size_t count = std::count_if(polygons.begin(), polygons.end(),
      [](const Polygon& p) { return p.points.size() % 2 == 0; });
    std::cout << count << std::endl;
  }

  void countOdd(const std::vector<Polygon>& polygons)
  {
    size_t count = std::count_if(polygons.begin(), polygons.end(),
      [](const Polygon& p) { return p.points.size() % 2 == 1; });
    std::cout << count << std::endl;
  }

  void countVertex(const std::vector<Polygon>& polygons, size_t vertexCount)
  {
    if (vertexCount < 3)
    {
      std::cout << "<INVALID COMMAND>" << std::endl;
      return;
    }
    
    size_t count = std::count_if(polygons.begin(), polygons.end(),
      [vertexCount](const Polygon& p) { return p.points.size() == vertexCount; });
    std::cout << count << std::endl;
  }

  // ECHO: дублирует вхождения указанной фигуры
  void echo(std::vector<Polygon>& polygons, const Polygon& target)
  {
    size_t addedCount = 0;
    
    for (auto it = polygons.begin(); it != polygons.end(); ++it)
    {
      if (*it == target)
      {
        it = polygons.insert(it + 1, target);
        addedCount++;
      }
    }
    
    std::cout << addedCount << std::endl;
  }

  // INFRAME: проверяет, лежит ли фигура внутри ограничивающего прямоугольника
  void inframe(const std::vector<Polygon>& polygons, const Polygon& target)
  {
    if (polygons.empty())
    {
      std::cout << "<INVALID COMMAND>" << std::endl;
      return;
    }
    
    bool result = isInFrame(target, polygons);
    std::cout << (result ? "<TRUE>" : "<FALSE>") << std::endl;
  }

  void processCommand(std::vector<Polygon>& polygons, const std::string& line)
  {
    std::istringstream iss(line);
    std::string command;
    iss >> command;

    if (command == "AREA")
    {
      std::string param;
      iss >> param;
      if (param == "EVEN") areaEven(polygons);
      else if (param == "ODD") areaOdd(polygons);
      else if (param == "MEAN") areaMean(polygons);
      else
      {
        size_t vertexCount = std::stoul(param);
        areaVertex(polygons, vertexCount);
      }
    }
    else if (command == "MAX")
    {
      std::string param;
      iss >> param;
      if (param == "AREA") maxArea(polygons);
      else if (param == "VERTEXES") maxVertexes(polygons);
      else std::cout << "<INVALID COMMAND>" << std::endl;
    }
    else if (command == "MIN")
    {
      std::string param;
      iss >> param;
      if (param == "AREA") minArea(polygons);
      else if (param == "VERTEXES") minVertexes(polygons);
      else std::cout << "<INVALID COMMAND>" << std::endl;
    }
    else if (command == "COUNT")
    {
      std::string param;
      iss >> param;
      if (param == "EVEN") countEven(polygons);
      else if (param == "ODD") countOdd(polygons);
      else
      {
        size_t vertexCount = std::stoul(param);
        countVertex(polygons, vertexCount);
      }
    }
    else if (command == "ECHO")
    {
      Polygon target;
      iss >> target;
      if (iss.fail() || target.points.empty())
      {
        std::cout << "<INVALID COMMAND>" << std::endl;
        return;
      }
      echo(polygons, target);
    }
    else if (command == "INFRAME")
    {
      Polygon target;
      iss >> target;
      if (iss.fail() || target.points.empty())
      {
        std::cout << "<INVALID COMMAND>" << std::endl;
        return;
      }
      inframe(polygons, target);
    }
    else
    {
      std::cout << "<INVALID COMMAND>" << std::endl;
    }
  }
}