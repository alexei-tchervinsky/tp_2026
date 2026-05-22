#include <algorithm>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <set>
#include <sstream>
#include <string>
#include <vector>

struct Point
{
  int x;
  int y;
};

struct Polygon
{
  std::vector< Point > points;
};

bool operator==(const Point& a, const Point& b)
{
  return a.x == b.x && a.y == b.y;
}

bool operator==(const Polygon& a, const Polygon& b)
{
  return a.points == b.points;
}

std::istream& operator>>(std::istream& in, Point& point)
{
  char left = '\0';
  char semicolon = '\0';
  char right = '\0';

  in >> left >> point.x >> semicolon >> point.y >> right;

  if (left != '(' || semicolon != ';' || right != ')')
  {
    in.setstate(std::ios::failbit);
  }

  return in;
}

std::istream& operator>>(std::istream& in, Polygon& poly)
{
  std::size_t count = 0;
  in >> count;

  if (!in || count < 3)
  {
    in.setstate(std::ios::failbit);
    return in;
  }

  poly.points.clear();
  std::set< std::pair< int, int > > uniquePoints;

  for (std::size_t i = 0; i < count; ++i)
  {
    Point p;
    in >> p;

    if (!in)
    {
      in.setstate(std::ios::failbit);
      return in;
    }

    if (uniquePoints.count({ p.x, p.y }) > 0)
    {
      in.setstate(std::ios::failbit);
      return in;
    }

    uniquePoints.insert({ p.x, p.y });
    poly.points.push_back(p);
  }

  return in;
}

bool readPolygon(std::istringstream& iss, Polygon& poly)
{
  if (!(iss >> poly))
  {
    return false;
  }

  std::string extra;
  if (iss >> extra)
  {
    return false;
  }

  return true;
}

double getArea(const Polygon& poly)
{
  double area = 0.0;

  for (std::size_t i = 0; i < poly.points.size(); ++i)
  {
    std::size_t j = (i + 1) % poly.points.size();
    area += poly.points[i].x * poly.points[j].y;
    area -= poly.points[j].x * poly.points[i].y;
  }

  return std::abs(area) / 2.0;
}

bool arePerms(const Polygon& a, const Polygon& b)
{
  if (a.points.size() != b.points.size())
  {
    return false;
  }

  std::vector< std::pair< int, int > > first;
  std::vector< std::pair< int, int > > second;

  for (const Point& p : a.points)
  {
    first.push_back({ p.x, p.y });
  }

  for (const Point& p : b.points)
  {
    second.push_back({ p.x, p.y });
  }

  std::sort(first.begin(), first.end());
  std::sort(second.begin(), second.end());

  return first == second;
}

bool isInFrame(const std::vector< Polygon >& polygons, const Polygon& target)
{
  if (polygons.empty())
  {
    return false;
  }

  int minX = polygons[0].points[0].x;
  int maxX = polygons[0].points[0].x;
  int minY = polygons[0].points[0].y;
  int maxY = polygons[0].points[0].y;

  for (const Polygon& poly : polygons)
  {
    for (const Point& p : poly.points)
    {
      minX = std::min(minX, p.x);
      maxX = std::max(maxX, p.x);
      minY = std::min(minY, p.y);
      maxY = std::max(maxY, p.y);
    }
  }

  for (const Point& p : target.points)
  {
    if (p.x < minX || p.x > maxX || p.y < minY || p.y > maxY)
    {
      return false;
    }
  }

  return true;
}

long long cross(const Point& a, const Point& b, const Point& c)
{
  return 1LL * (b.x - a.x) * (c.y - a.y) - 1LL * (b.y - a.y) * (c.x - a.x);
}

bool onSegment(const Point& a, const Point& b, const Point& p)
{
  return cross(a, b, p) == 0 &&
         std::min(a.x, b.x) <= p.x && p.x <= std::max(a.x, b.x) &&
         std::min(a.y, b.y) <= p.y && p.y <= std::max(a.y, b.y);
}

bool segmentsIntersect(const Point& a, const Point& b, const Point& c, const Point& d)
{
  long long c1 = cross(a, b, c);
  long long c2 = cross(a, b, d);
  long long c3 = cross(c, d, a);
  long long c4 = cross(c, d, b);

  if (c1 == 0 && onSegment(a, b, c)) return true;
  if (c2 == 0 && onSegment(a, b, d)) return true;
  if (c3 == 0 && onSegment(c, d, a)) return true;
  if (c4 == 0 && onSegment(c, d, b)) return true;

  return (c1 > 0) != (c2 > 0) && (c3 > 0) != (c4 > 0);
}

bool pointInsidePolygon(const Polygon& poly, const Point& p)
{
  bool inside = false;
  std::size_t n = poly.points.size();

  for (std::size_t i = 0, j = n - 1; i < n; j = i++)
  {
    const Point& a = poly.points[i];
    const Point& b = poly.points[j];

    if (onSegment(a, b, p))
    {
      return true;
    }

    bool intersect =
  ((a.y > p.y) != (b.y > p.y)) &&
  (p.x < static_cast<double>(b.x - a.x) *
  (p.y - a.y) / (b.y - a.y) + a.x);

    if (intersect)
    {
      inside = !inside;
    }
  }

  return inside;
}

bool polygonsIntersect(const Polygon& a, const Polygon& b)
{
  for (std::size_t i = 0; i < a.points.size(); ++i)
  {
    Point a1 = a.points[i];
    Point a2 = a.points[(i + 1) % a.points.size()];

    for (std::size_t j = 0; j < b.points.size(); ++j)
    {
      Point b1 = b.points[j];
      Point b2 = b.points[(j + 1) % b.points.size()];

      if (segmentsIntersect(a1, a2, b1, b2))
      {
        return true;
      }
    }
  }

  return pointInsidePolygon(a, b.points[0]) || pointInsidePolygon(b, a.points[0]);
}

bool hasRightAngle(const Polygon& poly)
{
  for (std::size_t i = 0; i < poly.points.size(); ++i)
  {
    const Point& prev = poly.points[(i + poly.points.size() - 1) % poly.points.size()];
    const Point& cur = poly.points[i];
    const Point& next = poly.points[(i + 1) % poly.points.size()];

    int x1 = prev.x - cur.x;
    int y1 = prev.y - cur.y;
    int x2 = next.x - cur.x;
    int y2 = next.y - cur.y;

    if (x1 * x2 + y1 * y2 == 0)
    {
      return true;
    }
  }

  return false;
}

bool isRect(const Polygon& poly)
{
  return poly.points.size() == 4 && hasRightAngle(poly);
}

std::vector< std::pair< int, int > > normalizedPoints(const Polygon& poly)
{
  int minX = poly.points[0].x;
  int minY = poly.points[0].y;

  for (const Point& p : poly.points)
  {
    minX = std::min(minX, p.x);
    minY = std::min(minY, p.y);
  }

  std::vector< std::pair< int, int > > result;

  for (const Point& p : poly.points)
  {
    result.push_back({ p.x - minX, p.y - minY });
  }

  std::sort(result.begin(), result.end());
  return result;
}

bool sameByTranslation(const Polygon& a, const Polygon& b)
{
  if (a.points.size() != b.points.size())
  {
    return false;
  }

  return normalizedPoints(a) == normalizedPoints(b);
}

int main(int argc, char* argv[])
{
  if (argc != 2)
  {
    std::cerr << "ERROR\n";
    return 1;
  }

  std::ifstream file(argv[1]);

  if (!file)
  {
    std::cerr << "ERROR\n";
    return 1;
  }

  std::vector< Polygon > polygons;
  std::string fileLine;

  while (std::getline(file, fileLine))
  {
    std::istringstream iss(fileLine);
    Polygon poly;

    if (readPolygon(iss, poly))
    {
      polygons.push_back(poly);
    }
  }

  std::cout << std::fixed << std::setprecision(1);

  std::string line;

  while (std::getline(std::cin, line))
  {
    if (line.empty())
    {
      continue;
    }

    std::istringstream iss(line);
    std::string command;
    iss >> command;

    if (command == "AREA")
    {
      std::string option;
      iss >> option;

      std::string extra;
      if (option.empty() || (iss >> extra))
      {
        std::cout << "<INVALID COMMAND>\n";
        continue;
      }

      double result = 0.0;

      if (option == "EVEN")
      {
        for (const Polygon& poly : polygons)
        {
          if (poly.points.size() % 2 == 0)
          {
            result += getArea(poly);
          }
        }
        std::cout << result << "\n";
      }
      else if (option == "ODD")
      {
        for (const Polygon& poly : polygons)
        {
          if (poly.points.size() % 2 == 1)
          {
            result += getArea(poly);
          }
        }
        std::cout << result << "\n";
      }
      else if (option == "MEAN")
      {
        if (polygons.empty())
        {
          std::cout << "<INVALID COMMAND>\n";
          continue;
        }

        for (const Polygon& poly : polygons)
        {
          result += getArea(poly);
        }

        std::cout << result / polygons.size() << "\n";
      }
      else
      {
        try
        {
          std::size_t pos = 0;
          int vertices = std::stoi(option, &pos);

          if (pos != option.size() || vertices < 3)
          {
            std::cout << "<INVALID COMMAND>\n";
            continue;
          }

          for (const Polygon& poly : polygons)
          {
            if (static_cast<int>(poly.points.size()) == vertices)
            {
              result += getArea(poly);
            }
          }

          std::cout << result << "\n";
        }
        catch (...)
        {
          std::cout << "<INVALID COMMAND>\n";
        }
      }
    }
    else if (command == "MAX")
    {
      std::string option;
      iss >> option;

      std::string extra;
      if (option.empty() || (iss >> extra) || polygons.empty())
      {
        std::cout << "<INVALID COMMAND>\n";
        continue;
      }

      if (option == "AREA")
      {
        double maxArea = 0.0;

        for (const Polygon& poly : polygons)
        {
          maxArea = std::max(maxArea, getArea(poly));
        }

        std::cout << maxArea << "\n";
      }
      else if (option == "VERTEXES")
      {
        std::size_t maxVertices = 0;

        for (const Polygon& poly : polygons)
        {
          maxVertices = std::max(maxVertices, poly.points.size());
        }

        std::cout << maxVertices << "\n";
      }
      else
      {
        std::cout << "<INVALID COMMAND>\n";
      }
    }
    else if (command == "MIN")
    {
      std::string option;
      iss >> option;

      std::string extra;
      if (option.empty() || (iss >> extra) || polygons.empty())
      {
        std::cout << "<INVALID COMMAND>\n";
        continue;
      }

      if (option == "AREA")
      {
        double minArea = std::numeric_limits< double >::max();

        for (const Polygon& poly : polygons)
        {
          minArea = std::min(minArea, getArea(poly));
        }

        std::cout << minArea << "\n";
      }
      else if (option == "VERTEXES")
      {
        std::size_t minVertices = polygons.front().points.size();

        for (const Polygon& poly : polygons)
        {
          minVertices = std::min(minVertices, poly.points.size());
        }

        std::cout << minVertices << "\n";
      }
      else
      {
        std::cout << "<INVALID COMMAND>\n";
      }
    }
    else if (command == "COUNT")
    {
      std::string option;
      iss >> option;

      std::string extra;
      if (option.empty() || (iss >> extra))
      {
        std::cout << "<INVALID COMMAND>\n";
        continue;
      }

      int count = 0;

      if (option == "EVEN")
      {
        for (const Polygon& poly : polygons)
        {
          if (poly.points.size() % 2 == 0)
          {
            ++count;
          }
        }

        std::cout << count << "\n";
      }
      else if (option == "ODD")
      {
        for (const Polygon& poly : polygons)
        {
          if (poly.points.size() % 2 == 1)
          {
            ++count;
          }
        }

        std::cout << count << "\n";
      }
      else
      {
        try
        {
          std::size_t pos = 0;
          int vertices = std::stoi(option, &pos);

          if (pos != option.size() || vertices < 3)
          {
            std::cout << "<INVALID COMMAND>\n";
            continue;
          }

          for (const Polygon& poly : polygons)
          {
            if (static_cast<int>(poly.points.size()) == vertices)
            {
              ++count;
            }
          }

          std::cout << count << "\n";
        }
        catch (...)
        {
          std::cout << "<INVALID COMMAND>\n";
        }
      }
    }
    else if (command == "ECHO")
{
  Polygon poly;

  if (std::cin >> poly)
  {
    polygons.push_back(poly);

    std::cout << polygons.size() << "\n";
  }
  else
  {
    std::cout << "<INVALID COMMAND>\n";

    std::cin.clear();

    std::string trash;
    std::getline(std::cin, trash);
  }
}
    else if (command == "PERMS")
    {
      Polygon target;

      if (!readPolygon(iss, target))
      {
        std::cout << "<INVALID COMMAND>\n";
        continue;
      }

      int count = 0;

      for (const Polygon& poly : polygons)
      {
        if (arePerms(poly, target))
        {
          ++count;
        }
      }

      std::cout << count << "\n";
    }
    else if (command == "INFRAME")
    {
      Polygon target;

      if (!readPolygon(iss, target))
      {
        std::cout << "<INVALID COMMAND>\n";
        continue;
      }

      std::cout << (isInFrame(polygons, target) ? "<TRUE>" : "<FALSE>") << "\n";
    }
    else if (command == "ECHO")
    {
      Polygon target;

      if (!readPolygon(iss, target))
      {
        std::cout << "<INVALID COMMAND>\n";
        continue;
      }

      std::vector< Polygon > result;
      int added = 0;

      for (const Polygon& poly : polygons)
      {
        result.push_back(poly);

        if (poly == target)
        {
          result.push_back(poly);
          ++added;
        }
      }

      polygons = result;
      std::cout << added << "\n";
    }
    else if (command == "RMECHO")
    {
      Polygon target;

      if (!readPolygon(iss, target))
      {
        std::cout << "<INVALID COMMAND>\n";
        continue;
      }

      std::vector< Polygon > result;
      int removed = 0;

      for (std::size_t i = 0; i < polygons.size(); ++i)
      {
        if (i > 0 && polygons[i] == target && polygons[i - 1] == target)
        {
          ++removed;
        }
        else
        {
          result.push_back(polygons[i]);
        }
      }

      polygons = result;
      std::cout << removed << "\n";
    }
    else if (command == "MAXSEQ")
    {
      Polygon target;

      if (!readPolygon(iss, target))
      {
        std::cout << "<INVALID COMMAND>\n";
        continue;
      }

      int best = 0;
      int cur = 0;

      for (const Polygon& poly : polygons)
      {
        if (poly == target)
        {
          ++cur;
          best = std::max(best, cur);
        }
        else
        {
          cur = 0;
        }
      }

      std::cout << best << "\n";
    }
    else if (command == "LESSAREA")
    {
      Polygon target;

      if (!readPolygon(iss, target))
      {
        std::cout << "<INVALID COMMAND>\n";
        continue;
      }

      double targetArea = getArea(target);
      int count = 0;

      for (const Polygon& poly : polygons)
      {
        if (getArea(poly) < targetArea)
        {
          ++count;
        }
      }

      std::cout << count << "\n";
    }
    else if (command == "SAME")
    {
      Polygon target;

      if (!readPolygon(iss, target))
      {
        std::cout << "<INVALID COMMAND>\n";
        continue;
      }

      int count = 0;

      for (const Polygon& poly : polygons)
      {
        if (sameByTranslation(poly, target))
        {
          ++count;
        }
      }

      std::cout << count << "\n";
    }
    else if (command == "RECTS")
    {
      std::string extra;
      if (iss >> extra)
      {
        std::cout << "<INVALID COMMAND>\n";
        continue;
      }

      int count = 0;

      for (const Polygon& poly : polygons)
      {
        if (isRect(poly))
        {
          ++count;
        }
      }

      std::cout << count << "\n";
    }
    else if (command == "RIGHTSHAPES")
    {
      std::string extra;
      if (iss >> extra)
      {
        std::cout << "<INVALID COMMAND>\n";
        continue;
      }

      int count = 0;

      for (const Polygon& poly : polygons)
      {
        if (hasRightAngle(poly))
        {
          ++count;
        }
      }

      std::cout << count << "\n";
    }
    else if (command == "INTERSECTIONS")
    {
      Polygon target;

      if (!readPolygon(iss, target))
      {
        std::cout << "<INVALID COMMAND>\n";
        continue;
      }

      int count = 0;

      for (const Polygon& poly : polygons)
      {
        if (polygonsIntersect(poly, target))
        {
          ++count;
        }
      }

      std::cout << count << "\n";
    }
    else
    {
      std::cout << "<INVALID COMMAND>\n";
    }
  }

  return 0;
}
