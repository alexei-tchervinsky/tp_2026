#include "Geometry.hpp"

#include <cassert>
#include <cmath>
#include <exception>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace
{
  bool areEqual(double lhs, double rhs)
  {
    return std::abs(lhs - rhs) < 0.000001;
  }

  Polygon makeTriangle()
  {
    return {{{0, 0}, {2, 0}, {0, 2}}};
  }

  Polygon makeSquare()
  {
    return {{{0, 0}, {0, 2}, {2, 2}, {2, 0}}};
  }

  Polygon makeFarSquare()
  {
    return {{{5, 5}, {5, 7}, {7, 7}, {7, 5}}};
  }

  void runTests()
  {
    const Polygon triangle = makeTriangle();
    const Polygon square = makeSquare();
    const Polygon farSquare = makeFarSquare();

    assert(areEqual(getArea(triangle), 2.0));
    assert(areEqual(getArea(square), 4.0));

    std::vector< Polygon > polygons{
      triangle,
      triangle,
      square,
      square,
      triangle,
      triangle,
      triangle
    };

    assert(removeEchoes(polygons, triangle) == 3);
    assert(polygons.size() == 4);
    assert(polygons[0] == triangle);
    assert(polygons[1] == square);
    assert(polygons[2] == square);
    assert(polygons[3] == triangle);

    const std::vector< Polygon > frame{square, farSquare};
    assert(isInFrame(frame, {{{1, 1}, {3, 3}, {6, 1}}}));
    assert(!isInFrame(frame, {{{-1, -1}, {1, 1}, {1, 0}}}));

    std::vector< Polygon > commandPolygons{triangle, square, farSquare};
    std::ostringstream output;

    executeCommand("AREA ODD", commandPolygons, output);
    assert(output.str() == "2.0\n");

    output.str("");
    output.clear();
    executeCommand("AREA EVEN", commandPolygons, output);
    assert(output.str() == "8.0\n");

    output.str("");
    output.clear();
    executeCommand("COUNT 4", commandPolygons, output);
    assert(output.str() == "2\n");

    output.str("");
    output.clear();
    executeCommand("INFRAME 3 (1;1) (3;3) (6;1)", commandPolygons, output);
    assert(output.str() == "<TRUE>\n");

    output.str("");
    output.clear();
    executeCommand("UNKNOWN", commandPolygons, output);
    assert(output.str() == "<INVALID COMMAND>\n");

    std::cout << "All tests passed\n";
  }
}

int main(int argc, char* argv[])
{
  if (argc == 2 && std::string(argv[1]) == "--test")
  {
    runTests();
    return 0;
  }

  if (argc != 2)
  {
    std::cerr << "Error: filename is not specified\n";
    return 1;
  }

  try
  {
    std::vector< Polygon > polygons = readPolygons(argv[1]);
    processCommands(std::cin, polygons, std::cout);
  }
  catch (const std::exception& exception)
  {
    std::cerr << "Error: " << exception.what() << '\n';
    return 1;
  }

  return 0;
}
