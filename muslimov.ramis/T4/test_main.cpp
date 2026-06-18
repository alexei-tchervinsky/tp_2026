// #include <gtest/gtest.h>
#include <iostream>
#include <iomanip>
#include <memory>

#include "demo_shapes.hpp"
#include "shapeContainer.hpp"
#include "shapePrinter.hpp"
#include "compositeShape.hpp"

int main() {
    // ::testing::InitGoogleTest(&argc, argv);
    // int testResult = RUN_ALL_TESTS();

    // Демонстрационный вывод — сразу после выполнения тестов
    try {
        // Создаём демонстрационный контейнер
    //(в нём минимум 5 фигур, одна составная)
        ShapesContainer container = createDemoContainer();

        // Установим формат вывода чисел
        std::cout << std::fixed << std::setprecision(2);

        // Вывод до масштабирования
        const auto &items = container.components();
        for (const auto &p : items) {
            // Если это составная фигура — печатаем многострочно
            if (const CompositeShape *comp = dynamic_cast<const CompositeShape*>(p.get())) {
                shapes_ui::printComposite(std::cout, *comp);
            } else {
                shapes_ui::printSimple(std::cout, *p);
                std::cout << "\n";
            }
        }

        // Масштабируем в 2 раза (изотропно)
        container.scaleAll(2.0);

        // Вывод после масштабирования
        for (const auto &p : items) {
            if (const CompositeShape *comp = dynamic_cast<const CompositeShape*>(p.get())) {
                shapes_ui::printComposite(std::cout, *comp);
            } else {
                shapes_ui::printSimple(std::cout, *p);
                std::cout << "\n";
            }
        }
    } catch (const std::exception &e) {
        std::cerr << "Demo printing failed: " << e.what() << "\n";
        return 2;
    }
    return 0;
}
