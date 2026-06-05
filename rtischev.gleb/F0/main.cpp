#include "dict.hpp"
#include <iostream>
#include <string>

int main()
{
    HashTable dict(41);

    int choice;
    std::string word, translation;

    while (std::cin >> choice)
    {
        switch (choice)
        {
        case 1:
        {
            std::cin >> word >> translation;

            try
            {
                if (dict.insert(word, translation))
                {
                    std::cout << "Перевод добавлен.\n";
                }
                else
                {
                    std::cout << "Не удалось добавить перевод.\n";
                }
            }
            catch (const std::invalid_argument &e)
            {
                std::cout << "Ошибка: " << e.what() << std::endl;
            }
            break;
        }
        case 2:
        {
            std::cin >> word;

            try
            {
                auto *entry = dict.find(word);
                if (entry)
                {
                    std::cout << "Переводы слова '" << word << "': ";
                    for (const auto &t : entry->translations_)
                    {
                        std::cout << t << " ";
                    }
                    std::cout << std::endl;
                }
                else
                {
                    std::cout << "Слово '" << word << "' не найдено.\n";
                }
            }
            catch (const std::invalid_argument &e)
            {
                std::cout << "Ошибка: " << e.what() << std::endl;
            }
            break;
        }
        case 3:
        {
            std::cin >> word;

            try
            {
                if (dict.remove(word))
                {
                    std::cout << "Слово удалено.\n";
                }
                else
                {
                    std::cout << "Слово не найдено.\n";
                }
            }
            catch (const std::invalid_argument &e)
            {
                std::cout << "Ошибка: " << e.what() << std::endl;
            }
            break;
        }
        case 4:
        {
            dict.print();
            break;
        }
        case 5:
        {
            std::cout << "Количество слов: " << dict.get_number() << std::endl;
            std::cout << "Количество коллизий: " << dict.get_collisions() << std::endl;
            break;
        }
        case 0:
        {
            return 0;
        }
        default:
            std::cout << "Неверный код команды.\n";
        }
    }

    return 0;
}
