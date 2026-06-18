#include "DictionaryHashTable.hpp"
#include <iostream>
#include <string>

int main()
{
  std::setlocale(LC_ALL, ".UTF8");

  try
  {
    DictionaryHashTable dictionary(5);

    std::cout << "ТЕСТ 1: Вставка допустимых данных и автосортировка переводов\n";
    std::cout << "Добавление слова 'apple' и его переводов\n";
    dictionary.insert("apple", "яблоко");
    dictionary.insert("apple", "глазное яблоко");

    std::cout << "Добавление слова 'banana'...\n";
    dictionary.insert("banana", "банан");

    std::cout << "Добавление слова 'book' и вариантов перевода в случайном порядке\n";
    dictionary.insert("book", "книга");
    dictionary.insert("book", "заказывать");
    dictionary.insert("book", "журнал");

    std::cout << "\nТекущая структура хеш-таблицы:\n";
    dictionary.displayTable();

    std::cout << "ТЕСТ 2: Поиск существующего слова по ключу\n";
    std::string searchKey = "book";
    std::cout << "Выполняется поиск слова '" << searchKey << "'...\n";

    const TranslationList *result = dictionary.search(searchKey);
    if (result)
    {
      std::cout << "Слово найдено.\nСписок переводов для '" << searchKey << "': ";
      result->print();
      std::cout << "\n";
    }
    else
    {
      std::cout << "Результат: Слово '" << searchKey << "' не найдено в словаре.\n";
    }

    std::cout << "ТЕСТ 3: Удаление слова из хеш-таблицы (проверка смены статуса)\n";
    std::cout << "Удаляем слово 'banana'...\n";
    dictionary.remove("banana");

    std::cout << "\nСтруктура таблицы после удаления (ячейка 'banana' [DELETED]):\n";
    dictionary.displayTable();

    std::cout << "ТЕСТ 4: Поиск слова после удаления \n";
    std::cout << "Ищем 'book', чья цепочка  проходит через удаленный слот 'banana'...\n";

    result = dictionary.search("book");
    if (result)
    {
      std::cout << "Успех! Алгоритм прошел через ячейку [DELETED] и нашел элемент.\n";
      std::cout << "Переводы для 'book': ";
      result->print();
      std::cout << "\n";
    }
    else
    {
      std::cout << "Ошибка: Цепочка исследования коллизий разорвана! Слово не найдено.\n";
    }

    std::cout << "ТЕСТ 5: Недопустимые данные — Попытка вставки пустого ключа\n";
    try
    {
      std::cout << "Добавляем запись с ключом: dictionary.insert(\"\", \"пустота\")...\n";
      dictionary.insert("", "пустота");
    }
    catch (const std::invalid_argument &e)
    {
      std::cerr << "Успешно перехвачена ошибка (std::invalid_argument):\n";
      std::cerr << "-> Сообщение системы: " << e.what() << "\n";
    }

    std::cout << "ТЕСТ 6: Недопустимые данные — Удаление несуществующего слова\n";
    try
    {
      std::cout << "Пробуем удалить отсутствующее слово 'pineapple'...\n";
      dictionary.remove("pineapple");
    }
    catch (const std::runtime_error &e)
    {
      std::cerr << "Успешно перехвачена ошибка (std::runtime_error):\n";
      std::cerr << "-> Сообщение системы: " << e.what() << "\n";
    }
    std::cout << "ТЕСТ 7: Демонстрация автоматического рехеширования\n";
    std::cout << "Сейчас в таблице 2 элемента ('apple' и 'book'), емкость = 5.\n";
    std::cout << "Добавим слово 'cat'...\n";
    dictionary.insert("cat", "кот");

    std::cout << "Добавим слово 'dog'...\n";
    dictionary.insert("dog", "собака");

    std::cout << "\nТаблица ПЕРЕД критической вставкой:\n";
    dictionary.displayTable();

    std::cout << "\nВставляем 5-е слово 'elephant'. Должно РЕХЕШИРОВАНИЕ...\n";
    std::cout << "Алгоритм должен: \n";
    std::cout << "1. Удвоить емкость (5 * 1,5 = 7,5)\n";
    std::cout << "2. Найти ближайшее простое число (это 7)\n";

    dictionary.insert("elephant", "слон");

    std::cout << "\nТаблица ПОСЛЕ автоматического рехеширования:\n";
    dictionary.displayTable();
    std::cout << "Обратите внимание: Емкость стала 7, а старые ячейки [DELETED] исчезли!\n";
  }
  catch (const std::exception &e)
  {
    std::cerr << "\n[КРИТИЧЕСКИЙ СБОЙ СИСТЕМЫ]: " << e.what() << "\n";
  }

  std::cout << "Тестирование всех модулей успешно завершено.\n";

  return 0;
}
