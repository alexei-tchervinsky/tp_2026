#include "FileReader.hpp"
#include <fstream>
#include <sstream>
#include <string>
#include <stdexcept>

KnapsackInstance FileReader::read(const std::string& filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
        throw std::invalid_argument("FileReader: cannot open file " + filename);

    std::string line;
    if (!std::getline(file, line))
        throw std::invalid_argument("FileReader: file is empty");

    size_t first = line.find_first_not_of(" \t\r\n");
    if (first == std::string::npos)
        throw std::invalid_argument("FileReader: capacity line is empty");

    line = line.substr(first);
    int capacity;
    try
    {
        capacity = std::stoi(line);
    }
    catch (...)
    {
        throw std::invalid_argument("FileReader: invalid capacity (not an integer)");
    }
    if (capacity < 0) throw std::invalid_argument("FileReader: capacity cannot be negative");

    KnapsackInstance instance(capacity);

    int lineNum = 2;
    while (std::getline(file, line))
    {
        if (line.find_first_not_of(" \t\r\n") == std::string::npos) continue;
        std::istringstream iss(line);
        int weight, value;
        if (!(iss >> weight >> value)) throw std::invalid_argument("FileReader: invalid format at line " + std::to_string(lineNum));
        if (weight < 0 || value < 0) throw std::invalid_argument("FileReader: weight or value negative at line " + std::to_string(lineNum));
        instance.addItem(Item(weight, value));
        ++lineNum;
    }

    return instance;
}
