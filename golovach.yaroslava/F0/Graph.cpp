#include "Graph.hpp"

#include <iostream>
#include <stdexcept>
#include <vector>

// ------------------------------------------------------------
// Конструктор — формирование пустого графа на n вершин
// ------------------------------------------------------------
Graph::Graph(int n) : nodeCount_(n), matrix_()
{
    if (n < 0)
        throw std::invalid_argument("Число вершин не может быть отрицательным");
    matrix_.resize(n);
    for (int i = 0; i < n; ++i)
        matrix_[i].resize(n, 0);
}
// ------------------------------------------------------------
// Проверка пуст ли граф
// ------------------------------------------------------------
bool Graph::isEmpty() const
{
    return nodeCount_ == 0;
}

// ------------------------------------------------------------
// Проверка наличия вершины в графе
// ------------------------------------------------------------
bool Graph::hasNode(int node) const
{
    return node >= 0 && node < nodeCount_;
}

// ------------------------------------------------------------
// Проверка наличия дуги между двумя узлами
// ------------------------------------------------------------
bool Graph::hasEdge(int from, int to) const
{
    validateNode(from);
    validateNode(to);
    return matrix_[from][to] != 0;
}

// ------------------------------------------------------------
// Добавдение вершины
// ------------------------------------------------------------
void Graph::addNode()
{
    nodeCount_++;
    for (auto& row : matrix_)
        row.push_back(0);
    matrix_.push_back(std::vector<int>(nodeCount_, 0));
}

// ------------------------------------------------------------
// Удалить вершину
// ------------------------------------------------------------
void Graph::removeNode(int node)
{
    validateNode(node);
    matrix_.erase(matrix_.begin() + node);
    for (auto& row : matrix_)
        row.erase(row.begin() + node);
    nodeCount_--;
}

// ------------------------------------------------------------
// Добавление дуги
// ------------------------------------------------------------
void Graph::addEdge(int from, int to, int weight)
{
    validateNode(from);
    validateNode(to);
    if (weight == 0)
        throw std::invalid_argument("Вес дуги не может быть равен нулю");
    matrix_[from][to] = weight;
}

// ------------------------------------------------------------
// Удаление дуги
// ------------------------------------------------------------
int Graph::removeEdge(int from, int to)
{
    validateNode(from);
    validateNode(to);
    if (!hasEdge(from, to))
        throw std::runtime_error("Дуга не существует");
    int weight = matrix_[from][to];
    matrix_[from][to] = 0;
    return weight;
}

// ============================================================
// Алгоритм 1: Входящие и исходящие степени каждой вершины
// ============================================================
void Graph::printDegrees() const
{
    if (isEmpty())
        throw std::runtime_error("Граф пуст");

    std::cout << "\n=== Степени вершин ===\n";
    for (int i = 0; i < nodeCount_; i++)
    {
        int outDegree = 0;
        int inDegree  = 0;

        for (int j = 0; j < nodeCount_; j++)
        {
            if (matrix_[i][j] != 0) outDegree++;
            if (matrix_[j][i] != 0) inDegree++;
        }

        std::cout << "Вершина " << i
                  << " | входящих: " << inDegree
                  << " | исходящих: " << outDegree << "\n";
    }
}

// ============================================================
// Алгоритм 2: Вершина с максимальной суммарной степенью
// ============================================================
int Graph::maxDegreeNode() const
{
    if (isEmpty())
        throw std::runtime_error("Граф пуст");

    int maxNode   = 0;
    int maxDegree = 0;

    for (int i = 0; i < nodeCount_; i++)
    {
        int degree = 0;
        for (int j = 0; j < nodeCount_; j++)
        {
            if (matrix_[i][j] != 0) degree++;
            if (matrix_[j][i] != 0) degree++;
        }
        if (degree > maxDegree)
        {
            maxDegree = degree;
            maxNode   = i;
        }
    }

    std::cout << "\n=== Максимальная степень ===\n";
    std::cout << "Вершина " << maxNode << " | суммарная степень: " << maxDegree << "\n";
    return maxNode;
}

// ============================================================
// Алгоритм 3: Удаление кратных рёбер и петель
// ============================================================
void Graph::removeMultipleEdgesAndLoops()
{
    if (isEmpty())
        throw std::runtime_error("Граф пуст");

    std::cout << "\n=== Удаление петель и кратных рёбер ===\n";
    for (int i = 0; i < nodeCount_; i++)
    {
        if (matrix_[i][i] != 0)
        {
            std::cout << "Удалена петля в вершине " << i << "\n";
            matrix_[i][i] = 0;
        }
        for (int j = 0; j < nodeCount_; j++)
        {
            if (i != j && matrix_[i][j] > 1)
            {
                std::cout << "Кратное ребро " << i << "->" << j << " заменено на одно\n";
                matrix_[i][j] = 1;
            }
        }
    }
    std::cout << "Готово.\n";
}

// ============================================================
// Алгоритм 4: Поиск истоков и стоков
// ============================================================
void Graph::findSourcesAndSinks() const
{
    if (isEmpty())
        throw std::runtime_error("Граф пуст");

    std::vector<int> sources;
    std::vector<int> sinks;

    for (int i = 0; i < nodeCount_; i++)
    {
        int inDegree  = 0;
        int outDegree = 0;

        for (int j = 0; j < nodeCount_; j++)
        {
            if (matrix_[j][i] != 0) inDegree++;
            if (matrix_[i][j] != 0) outDegree++;
        }

        if (inDegree == 0)  sources.push_back(i);
        if (outDegree == 0) sinks.push_back(i);
    }

    std::cout << "\n=== Истоки и стоки ===\n";

    if (sources.empty())
        std::cout << "Истоки: отсутствуют\n";
    else
    {
        std::cout << "Истоки (нет входящих дуг): ";
        for (int v : sources) std::cout << v << " ";
        std::cout << "\n";
    }

    if (sinks.empty())
        std::cout << "Стоки: отсутствуют\n";
    else
    {
        std::cout << "Стоки (нет исходящих дуг): ";
        for (int v : sinks) std::cout << v << " ";
        std::cout << "\n";
    }
}

// ------------------------------------------------------------
// Вывод матрицы смежности
// ------------------------------------------------------------
void Graph::printMatrix() const
{
    std::cout << "\n=== Матрица смежности ===\n";
    std::cout << "  ";
    for (int i = 0; i < nodeCount_; i++) std::cout << i << " ";
    std::cout << "\n";
    for (int i = 0; i < nodeCount_; i++)
    {
        std::cout << i << " ";
        for (int j = 0; j < nodeCount_; j++)
            std::cout << matrix_[i][j] << " ";
        std::cout << "\n";
    }
}

// ------------------------------------------------------------
// Проверка корректности индекса вершины
// ------------------------------------------------------------
void Graph::validateNode(int node) const
{
    if (!hasNode(node))
        throw std::out_of_range("Вершина " + std::to_string(node) + " не существует в графе");
}
