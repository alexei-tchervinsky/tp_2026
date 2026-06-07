#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char* argv[])
{
    std::cout << "Программа запущена" << std::endl;
    std::cout << "Аргументов: " << argc << std::endl;
    if (argc > 1)
        std::cout << "Имя файла: " << argv[1] << std::endl;

    std::ifstream file("input_data02_tegelekova_2026.txt");
    if (file.is_open())
    {
        std::cout << "Файл открыт!" << std::endl;
        file.close();
    }
    else
    {
        std::cout << "Не могу открыть файл!" << std::endl;
    }

    std::cout << "Нажмите Enter для выхода...";
    std::cin.get();
    return 0;
}
