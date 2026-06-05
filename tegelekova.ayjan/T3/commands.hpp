#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include "polygon.hpp"
#include <vector>
#include <string>
#include <functional>
#include <map>

namespace tchervinsky
{
  // Основные команды
  void areaEven(const std::vector<Polygon>& polygons);
  void areaOdd(const std::vector<Polygon>& polygons);
  void areaMean(const std::vector<Polygon>& polygons);
  void areaVertex(const std::vector<Polygon>& polygons, size_t vertexCount);
  void maxArea(const std::vector<Polygon>& polygons);
  void maxVertexes(const std::vector<Polygon>& polygons);
  void minArea(const std::vector<Polygon>& polygons);
  void minVertexes(const std::vector<Polygon>& polygons);
  void countEven(const std::vector<Polygon>& polygons);
  void countOdd(const std::vector<Polygon>& polygons);
  void countVertex(const std::vector<Polygon>& polygons, size_t vertexCount);

  // Команды варианта: ECHO и INFRAME
  void echo(std::vector<Polygon>& polygons, const Polygon& target);
  void inframe(const std::vector<Polygon>& polygons, const Polygon& target);

  // Парсинг команды
  void processCommand(std::vector<Polygon>& polygons, const std::string& line);
}

#endif