#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
#include <iomanip>
#include "polygon.hpp"

int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    std::cerr << "Error: filename parameter is missing.\n";
    return 1;
  }

  std::ifstream file(argv[1]);
  if (!file.is_open())
  {
    std::cerr << "Error: cannot open file " << argv[1] << "\n";
    return 1;
  }
  std::vector<Polygon> polygons;
  std::string file_line;
  while (std::getline(file, file_line))
  {
    if (file_line.empty())
      continue;
    std::stringstream ss(file_line);
    Polygon poly;
    if (parsePolygonFromStream(ss, poly))
    {
      polygons.push_back(poly);
    }
  }
  file.close();
  std::cout << std::fixed << std::setprecision(1);

  std::string command_line;
  while (std::getline(std::cin, command_line))
  {
    if (command_line.empty())
      continue;
    std::stringstream ss(command_line);
    std::string cmd;
    if (!(ss >> cmd))
    {
      std::cout << "<INVALID COMMAND>\n";
      continue;
    }

    if (cmd == "AREA")
    {
      std::string arg;
      if (!(ss >> arg))
      {
        std::cout << "<INVALID COMMAND>\n";
        continue;
      }
      char tr;
      if (ss >> tr)
      {
        std::cout << "<INVALID COMMAND>\n";
        continue;
      }

      if (arg == "EVEN")
      {
        double sum = std::accumulate(polygons.begin(), polygons.end(), 0.0, [](double s, const Polygon &p)
                                     { return p.points.size() % 2 == 0 ? s + getArea(p) : s; });
        std::cout << sum << "\n";
      }
      else if (arg == "ODD")
      {
        double sum = std::accumulate(polygons.begin(), polygons.end(), 0.0, [](double s, const Polygon &p)
                                     { return p.points.size() % 2 != 0 ? s + getArea(p) : s; });
        std::cout << sum << "\n";
      }
      else if (arg == "MEAN")
      {
        if (polygons.empty())
        {
          std::cout << "<INVALID COMMAND>\n";
        }
        else
        {
          double sum = std::accumulate(polygons.begin(), polygons.end(), 0.0, [](double s, const Polygon &p)
                                       { return s + getArea(p); });
          std::cout << (sum / polygons.size()) << "\n";
        }
      }
      else
      {
        try
        {
          size_t num = std::stoull(arg);
          double sum = std::accumulate(polygons.begin(), polygons.end(), 0.0, [num](double s, const Polygon &p)
                                       { return p.points.size() == num ? s + getArea(p) : s; });
          std::cout << sum << "\n";
        }
        catch (...)
        {
          std::cout << "<INVALID COMMAND>\n";
        }
      }
    }
    else if (cmd == "MAX")
    {
      std::string arg;
      if (!(ss >> arg) || polygons.empty())
      {
        std::cout << "<INVALID COMMAND>\n";
        continue;
      }
      char tr;
      if (ss >> tr)
      {
        std::cout << "<INVALID COMMAND>\n";
        continue;
      }

      if (arg == "AREA")
      {
        auto it = std::max_element(polygons.begin(), polygons.end(), [](const Polygon &a, const Polygon &b)
                                   { return getArea(a) < getArea(b); });
        std::cout << getArea(*it) << "\n";
      }
      else if (arg == "VERTEXES")
      {
        auto it = std::max_element(polygons.begin(), polygons.end(), [](const Polygon &a, const Polygon &b)
                                   { return a.points.size() < b.points.size(); });
        std::cout << it->points.size() << "\n";
      }
      else
      {
        std::cout << "<INVALID COMMAND>\n";
      }
    }
    else if (cmd == "MIN")
    {
      std::string arg;
      if (!(ss >> arg) || polygons.empty())
      {
        std::cout << "<INVALID COMMAND>\n";
        continue;
      }
      char tr;
      if (ss >> tr)
      {
        std::cout << "<INVALID COMMAND>\n";
        continue;
      }

      if (arg == "AREA")
      {
        auto it = std::min_element(polygons.begin(), polygons.end(), [](const Polygon &a, const Polygon &b)
                                   { return getArea(a) < getArea(b); });
        std::cout << getArea(*it) << "\n";
      }
      else if (arg == "VERTEXES")
      {
        auto it = std::min_element(polygons.begin(), polygons.end(), [](const Polygon &a, const Polygon &b)
                                   { return a.points.size() < b.points.size(); });
        std::cout << it->points.size() << "\n";
      }
      else
      {
        std::cout << "<INVALID COMMAND>\n";
      }
    }
    else if (cmd == "COUNT")
    {
      std::string arg;
      if (!(ss >> arg))
      {
        std::cout << "<INVALID COMMAND>\n";
        continue;
      }
      char tr;
      if (ss >> tr)
      {
        std::cout << "<INVALID COMMAND>\n";
        continue;
      }

      if (arg == "EVEN")
      {
        auto count = std::count_if(polygons.begin(), polygons.end(), [](const Polygon &p)
                                   { return p.points.size() % 2 == 0; });
        std::cout << count << "\n";
      }
      else if (arg == "ODD")
      {
        auto count = std::count_if(polygons.begin(), polygons.end(), [](const Polygon &p)
                                   { return p.points.size() % 2 != 0; });
        std::cout << count << "\n";
      }
      else
      {
        try
        {
          size_t num = std::stoull(arg);
          auto count = std::count_if(polygons.begin(), polygons.end(), [num](const Polygon &p)
                                     { return p.points.size() == num; });
          std::cout << count << "\n";
        }
        catch (...)
        {
          std::cout << "<INVALID COMMAND>\n";
        }
      }
    }
    else if (cmd == "RECTS")
    {
      char tr;
      if (ss >> tr)
      {
        std::cout << "<INVALID COMMAND>\n";
        continue;
      }
      auto count = std::count_if(polygons.begin(), polygons.end(), isRectangle);
      std::cout << count << "\n";
    }
    else if (cmd == "MAXSEQ")
    {
      Polygon target;
      if (!parsePolygonFromStream(ss, target))
      {
        std::cout << "<INVALID COMMAND>\n";
        continue;
      }

      struct SeqState
      {
        int max_seq = 0;
        int current_seq = 0;
        Polygon target;
      };

      SeqState final_state = std::accumulate(polygons.begin(), polygons.end(), SeqState{0, 0, target},
                                             [](SeqState state, const Polygon &poly)
                                             {
                                               if (poly == state.target)
                                               {
                                                 state.current_seq++;
                                                 if (state.current_seq > state.max_seq)
                                                 {
                                                   state.max_seq = state.current_seq;
                                                 }
                                               }
                                               else
                                               {
                                                 state.current_seq = 0;
                                               }
                                               return state;
                                             });

      std::cout << final_state.max_seq << "\n";
    }
    else
    {
      std::cout << "<INVALID COMMAND>\n";
    }
  }

  return 0;
}
