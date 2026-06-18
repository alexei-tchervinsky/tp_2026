#include <iostream>
#include <stdexcept>
#include <filesystem> // Подключаем для работы с размерами файлов
#include "HuffmanF0.hpp"

int main() {
    try {
        std::string input = "input.txt";
        std::string archive = "archive.huff";
        std::string output = "output.txt";

        HuffmanArchiver archiver;

        // Запуск архивации и распаковки
        archiver.compress(input, archive);
        archiver.decompress(archive, output);

        // Измеряем размеры файлов в байтах
        auto inputSize = std::filesystem::file_size(input);
        auto archiveSize = std::filesystem::file_size(archive);

        // Считаем процент (сколько места занимает сжатый файл от оригинала)
        double compressionRatio = (static_cast<double>(archiveSize) / inputSize) * 100.0;

        // Красивый вывод в терминал
        std::cout << "\n==============================================" << std::endl;
        std::cout << "  Huffman Archiver processed data successfully!" << std::endl;
        std::cout << "==============================================" << std::endl;
        std::cout << " Исходный файл (input.txt):   " << inputSize << " байт" << std::endl;
        std::cout << " Сжатый архив (archive.huff):  " << archiveSize << " байт" << std::endl;
        std::cout << " Результат сжатия:            " << compressionRatio << "% от исходного размера" << std::endl;
        std::cout << "==============================================" << std::endl;

    } catch (const std::exception& ex) {
        std::cerr << "Ошибка: " << ex.what() << std::endl;
        return 1;
    }
    return 0;
}
