#include "DataStruct.hpp"
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <sstream>   // для std::istringstream

int main()
{
    std::vector<DataStruct> data;
    std::string line;

    // Читаем построчно
    while (std::getline(std::cin, line))
    {
        // Создаём поток из строки и пытаемся прочитать DataStruct
        std::istringstream ss(line);
        DataStruct ds;
        if (ss >> ds)
        {
            data.push_back(ds);
        }
        // Если не удалось — просто игнорируем строку
    }

    // Сортируем
    std::sort(data.begin(), data.end(), compareDataStruct);

    // Выводим
    std::copy(data.begin(), data.end(),
              std::ostream_iterator<DataStruct>(std::cout, "\n"));

    return 0;
}
