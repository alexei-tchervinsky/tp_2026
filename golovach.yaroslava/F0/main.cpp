#include "Graph.hpp"
#include <iostream>

int main()
{
    std::cout << "==============================\n";
    std::cout << " ТЕСТ 1: Обычный граф\n";
    std::cout << "==============================\n";

    try
    {
        Graph g(5);
        g.addEdge(0, 1);
        g.addEdge(0, 2);
        g.addEdge(1, 3);
        g.addEdge(2, 3);
        g.addEdge(2, 4);
        g.addEdge(3, 4);

        g.printMatrix();
        g.printDegrees();
        g.maxDegreeNode();
        g.findSourcesAndSinks();
    }
    catch (const std::exception& ex)
    {
        std::cout << "[Ошибка]: " << ex.what() << "\n";
    }

    std::cout << "\n==============================\n";
    std::cout << " ТЕСТ 2: Мультиграф с петлями\n";
    std::cout << "==============================\n";

    try
    {
        Graph g(3);
        g.addEdge(0, 1, 3); // кратное ребро
        g.addEdge(1, 2);
        g.addEdge(2, 2);    // петля
        g.addEdge(0, 0);    // петля

        g.printMatrix();
        g.removeMultipleEdgesAndLoops();
        g.printMatrix();
        g.findSourcesAndSinks();
    }
    catch (const std::exception& ex)
    {
        std::cout << "[Ошибка]: " << ex.what() << "\n";
    }

    std::cout << "\n==============================\n";
    std::cout << " ТЕСТ 3: Недопустимые операции\n";
    std::cout << "==============================\n";

    try
    {
        Graph g(3);
        g.addEdge(0, 99); // несуществующая вершина
    }
    catch (const std::exception& ex)
    {
        std::cout << "[Ожидаемая ошибка]: " << ex.what() << "\n";
    }

    try
    {
        Graph g(3);
        g.removeEdge(0, 1); // дуги нет
    }
    catch (const std::exception& ex)
    {
        std::cout << "[Ожидаемая ошибка]: " << ex.what() << "\n";
    }

    try
    {
        Graph g(-1); // отрицательное число вершин
    }
    catch (const std::exception& ex)
    {
        std::cout << "[Ожидаемая ошибка]: " << ex.what() << "\n";
    }

    try
    {
        Graph g(0);
        g.findSourcesAndSinks(); // пустой граф
    }
    catch (const std::exception& ex)
    {
        std::cout << "[Ожидаемая ошибка]: " << ex.what() << "\n";
    }

    return 0;
}
