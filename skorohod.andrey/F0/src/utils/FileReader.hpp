#ifndef FILE_READER_HPP
#define FILE_READER_HPP

#include <string>
#include "../core/KnapsackInstance.hpp"

class FileReader
{
public:
    static KnapsackInstance read(const std::string& filename);
};

#endif
