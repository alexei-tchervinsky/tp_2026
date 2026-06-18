#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <functional>
#include <algorithm>
#include <numeric>
#include <iomanip>
#include <cctype>
#include <stdexcept>
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

  std::stringstream ss;
  std::map<std::string, std::function<void(void)>> cmds;

  cmds["AREA"] = [&ss, &polygons]()
  {
    std::string arg;
    if (!(ss >> arg))
      throw std::runtime_error("");
    char tr;
    if (ss >> tr)
      throw std::runtime_error("");

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
        throw std::runtime_error("");
      double sum = std::accumulate(polygons.begin(), polygons.end(), 0.0, [](double s, const Polygon &p)
                                   { return s + getArea(p); });
      std::cout << (sum / polygons.size()) << "\n";
    }
    else
    {
      if (arg.empty() || !std::all_of(arg.begin(), arg.end(), [](unsigned char c)
                                      { return std::isdigit(c); }))
      {
        throw std::runtime_error("");
      }
      size_t num = std::stoull(arg);
      if (num < 3)
        throw std::runtime_error("");
      double sum = std::accumulate(polygons.begin(), polygons.end(), 0.0, [num](double s, const Polygon &p)
                                   { return p.points.size() == num ? s + getArea(p) : s; });
      std::cout << sum << "\n";
    }
  };

  cmds["MAX"] = [&ss, &polygons]()
  {
    std::string arg;
    if (!(ss >> arg) || polygons.empty())
      throw std::runtime_error("");
    char tr;
    if (ss >> tr)
      throw std::runtime_error("");

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
      throw std::runtime_error("");
    }
  };

  cmds["MIN"] = [&ss, &polygons]()
  {
    std::string arg;
    if (!(ss >> arg) || polygons.empty())
      throw std::runtime_error("");
    char tr;
    if (ss >> tr)
      throw std::runtime_error("");

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
      throw std::runtime_error("");
    }
  };

  cmds["COUNT"] = [&ss, &polygons]()
  {
    std::string arg;
    if (!(ss >> arg))
      throw std::runtime_error("");
    char tr;
    if (ss >> tr)
      throw std::runtime_error("");

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
      if (arg.empty() || !std::all_of(arg.begin(), arg.end(), [](unsigned char c)
                                      { return std::isdigit(c); }))
      {
        throw std::runtime_error("");
      }
      size_t num = std::stoull(arg);
      if (num < 3)
        throw std::runtime_error("");
      auto count = std::count_if(polygons.begin(), polygons.end(), [num](const Polygon &p)
                                 { return p.points.size() == num; });
      std::cout << count << "\n";
    }
  };

  cmds["RECTS"] = [&ss, &polygons]()
  {
    char tr;
    if (ss >> tr)
      throw std::runtime_error("");
    auto count = std::count_if(polygons.begin(), polygons.end(), isRectangle);
    std::cout << count << "\n";
  };

  cmds["MAXSEQ"] = [&ss, &polygons]()
  {
    Polygon target;
    if (!parsePolygonFromStream(ss, target))
      throw std::runtime_error("");

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
  };

  std::string command_line;
  while (std::getline(std::cin, command_line))
  {
    if (command_line.empty())
      continue;

    ss.clear();
    ss.str(command_line);

    std::string command;
    if (!(ss >> command))
    {
      std::cout << "<INVALID COMMAND>\n";
      continue;
    }

    try
    {
      cmds.at(command)();
    }
    catch (...)
    {
      std::cout << "<INVALID COMMAND>\n";
    }
  }

  return 0;
}
