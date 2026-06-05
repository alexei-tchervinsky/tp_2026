#include "DataStruct.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <limits>
#include <sstream>

void testConstructorsAndOperators() {
    std::cout << "=== ТЕСТИРОВАНИЕ КОНСТРУКТОРОВ И ОПЕРАТОРОВ ===\n\n";

    std::cout << "1. Конструктор по умолчанию:\n";
    DataStruct ds1;
    std::cout << "   ds1 = " << ds1 << "\n\n";

    std::cout << "2. Конструктор с параметрами:\n";
    DataStruct ds2(0xFF, 'A', "Hello");
    std::cout << "   ds2 = " << ds2 << "\n\n";

    std::cout << "3. Копирующий конструктор:\n";
    DataStruct ds3(ds2);
    std::cout << "   ds3 (копия ds2) = " << ds3 << "\n";
    std::cout << "   ds2 = " << ds2 << "\n\n";

    std::cout << "4. Перемещающий конструктор:\n";
    DataStruct ds4(std::move(ds3));
    std::cout << "   ds4 (перемещён из ds3) = " << ds4 << "\n";
    std::cout << "   ds3 после перемещения = " << ds3 << "\n\n";

    std::cout << "5. Копирующее присваивание:\n";
    DataStruct ds5;
    ds5 = ds2;
    std::cout << "   ds5 (после ds5 = ds2) = " << ds5 << "\n";
    std::cout << "   ds2 = " << ds2 << "\n\n";

    std::cout << "6. Перемещающее присваивание:\n";
    DataStruct ds6;
    ds6 = std::move(ds5);
    std::cout << "   ds6 (после ds6 = move(ds5)) = " << ds6 << "\n";
    std::cout << "   ds5 после перемещения = " << ds5 << "\n\n";

    std::cout << "7. Самоприсваивание (копирование):\n";
    DataStruct ds7(0x123, 'X', "Test");
    ds7 = ds7;
    std::cout << "   ds7 после ds7 = ds7 = " << ds7 << "\n\n";


    std::cout << "9. Тест swap:\n";
    DataStruct ds9a(0x111, 'A', "First");
    DataStruct ds9b(0x999, 'Z', "Last");
    std::cout << "   До swap: ds9a = " << ds9a << ", ds9b = " << ds9b << "\n";
    ds9a.swap(ds9b);
    std::cout << "   После swap: ds9a = " << ds9a << ", ds9b = " << ds9b << "\n\n";

    std::cout << "=== ТЕСТИРОВАНИЕ ЗАВЕРШЕНО ===\n\n";
}

int main() {
    testConstructorsAndOperators();

    std::cout << "=== ОСНОВНАЯ ПРОГРАММА ===\n";
    std::cout << "Введите данные в формате (:key1 0xFF:key2 'A':key3 \"Hello\":)\n";
    std::cout << "Для завершения ввода нажмите Ctrl+D (или Ctrl+Z в Windows)\n\n";

    std::vector<DataStruct> dataVector;

    std::istream_iterator<DataStruct> inputIt(std::cin);
    std::istream_iterator<DataStruct> endIt;

    std::copy(inputIt, endIt, std::back_inserter(dataVector));

    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (dataVector.empty()) {
        std::cout << "Нет корректных данных для обработки.\n";
        return 0;
    }

    std::cout << "\nСчитано " << dataVector.size() << " записей:\n";
    std::copy(dataVector.begin(), dataVector.end(),
              std::ostream_iterator<DataStruct>(std::cout, "\n"));

    DataStructComparator comparator;
    std::sort(dataVector.begin(), dataVector.end(), comparator);

    std::cout << "\n=== ПОСЛЕ СОРТИРОВКИ ===\n";
    std::cout << "(по key1, затем по key2, затем по длине key3)\n\n";

    std::ostream_iterator<DataStruct> outputIt(std::cout, "\n");
    std::copy(dataVector.begin(), dataVector.end(), outputIt);

    return 0;
}
