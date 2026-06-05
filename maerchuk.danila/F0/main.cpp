#include "Graph.hpp"
#include "GraphAlgorithms.hpp"
#include "GraphExceptions.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <limits>

using namespace graph_project;

void printPath(const std::vector<std::string>& path) {
    for (size_t i = 0; i < path.size(); ++i) {
        std::cout << path[i];
        if (i < path.size() - 1) {
            std::cout << " -> ";
        }
    }
    std::cout << std::endl;
}

int main() {
    DirectedWeightedGraph graph;

    graph.addVertex("A");
    graph.addVertex("B");
    graph.addVertex("C");
    graph.addVertex("D");
    graph.addVertex("E");
    graph.addVertex("Isolated");

    graph.addEdge("A", "B", 4.0);
    graph.addEdge("A", "C", 2.0);
    graph.addEdge("B", "C", 3.0);
    graph.addEdge("B", "D", 2.0);
    graph.addEdge("C", "B", 1.0);
    graph.addEdge("C", "D", 4.0);
    graph.addEdge("C", "E", 5.0);
    graph.addEdge("D", "E", 1.0);

    std::cout << "=== 1. TESTING DIJKSTRA ALGORITHM ===" << std::endl;
    try {
        ShortestPathResult res = GraphAlgorithms::dijkstra(graph, "A");
        for (const auto& v : graph.getAllVertices()) {
            if (v == "Isolated") continue;
            std::cout << "Distance from A to " << v << " = " << res.distances[v] << " | Path: ";
            printPath(res.reconstructPath(v));
        }
    } catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
    }

    std::cout << "\n=== 2. TESTING WAVE ALGORITHM (BFS) ===" << std::endl;
    try {
        std::cout << "Finding shortest path (by number of edges) from A to E: " << std::endl;
        auto wave_path = GraphAlgorithms::waveAlgorithm(graph, "A", "E");
        std::cout << "Path: ";
        printPath(wave_path);
    } catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
    }

    std::cout << "\n=== 3. TESTING BELLMAN-FORD ALGORITHM ===" << std::endl;
    try {
        graph.addEdge("B", "E", -2.0);
        ShortestPathResult res = GraphAlgorithms::bellmanFord(graph, "A");
        std::cout << "Distance from A to E = " << res.distances["E"] << " | Path: ";
        printPath(res.reconstructPath("E"));
    } catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
    }

    std::cout << "\n=== 4. EXCEPTION HANDLING TEST SCENARIOS ===" << std::endl;

    // Сценарий 1: Дублирование вершины
    try {
        std::cout << "Attempting to add duplicate vertex 'A'..." << std::endl;
        graph.addVertex("A");
    } catch (const std::exception& ex) {
        std::cout << "Expected exception caught: " << ex.what() << std::endl;
    }

    // Сценарий 2: Путь не найден (изолированная вершина)
    try {
        std::cout << "Running Wave algorithm to an isolated vertex..." << std::endl;
        GraphAlgorithms::waveAlgorithm(graph, "A", "Isolated");
    } catch (const std::exception& ex) {
        std::cout << "Expected exception caught: " << ex.what() << std::endl;
    }

    // Сценарий 3: Реконструкция пути к изолированной вершине в Dijkstra
    try {
        std::cout << "Attempting to reconstruct path to an isolated vertex in Dijkstra..." << std::endl;
        ShortestPathResult res = GraphAlgorithms::dijkstra(graph, "A");
        res.reconstructPath("Isolated");
    } catch (const std::exception& ex) {
        std::cout << "Expected exception caught: " << ex.what() << std::endl;
    }

    // Сценарий 4: Запуск Dijkstra на графе с отрицательными рёбрами
    try {
        std::cout << "Running Dijkstra on a graph with a negative edge weight..." << std::endl;
        graph.addEdge("B", "E", -2.0);
        GraphAlgorithms::dijkstra(graph, "A");
    } catch (const std::exception& ex) {
        std::cout << "Expected exception caught: " << ex.what() << std::endl;
    }

    // Сценарий 5: Создание цикла с отрицательным весом для Bellman-Ford
    try {
        std::cout << "Running Bellman-Ford on a graph with a negative cycle..." << std::endl;
        graph.addEdge("E", "D", -2.0);
        GraphAlgorithms::bellmanFord(graph, "A");
    } catch (const std::exception& ex) {
        std::cout << "Expected exception caught: " << ex.what() << std::endl;
    }

    // Сценарий 6: Добавление ребра к несуществующей вершине
    try {
        std::cout << "Attempting to add an edge to a non-existent vertex..." << std::endl;
        graph.addEdge("A", "XYZ", 10.0);
    } catch (const std::exception& ex) {
        std::cout << "Expected exception caught: " << ex.what() << std::endl;
    }

    // Сценарий 7: Добавление ребра с некорректным весом (NaN)
    try {
        std::cout << "Attempting to add an edge with NaN weight..." << std::endl;
        graph.addEdge("A", "B", std::numeric_limits<double>::quiet_NaN());
    } catch (const std::exception& ex) {
        std::cout << "Expected exception caught: " << ex.what() << std::endl;
    }

    return 0;
}
