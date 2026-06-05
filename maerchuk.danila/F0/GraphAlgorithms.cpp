#include "GraphAlgorithms.hpp"
#include "GraphExceptions.hpp"
#include <queue>
#include <algorithm>

namespace graph_project {

std::vector<std::string> ShortestPathResult::reconstructPath(
    const std::string& target) const {

    auto dist_it = distances.find(target);
    if (dist_it == distances.end() || dist_it->second == GraphAlgorithms::INF) {
        throw PathNotFoundException("No path exists to target vertex: " + target);
    }

    std::vector<std::string> path;
    std::string current = target;
    while (!current.empty()) {
        path.push_back(current);
        auto pred_it = predecessors.find(current);
        if (pred_it != predecessors.end()) {
            current = pred_it->second;
        } else {
            current = "";
        }
    }
    std::reverse(path.begin(), path.end());
    return path;
}

// 1. Алгоритм DIJKSTRA
ShortestPathResult GraphAlgorithms::dijkstra(
    const DirectedWeightedGraph& graph,
    const std::string& start_id) {

    if (!graph.hasVertex(start_id)) {
        throw VertexNotFoundException(
            "Start vertex for Dijkstra not found: " + start_id);
    }

    ShortestPathResult result;
    auto vertices = graph.getAllVertices();

    for (const auto& v : vertices) {
        result.distances[v] = INF;
        result.predecessors[v] = "";
    }
    result.distances[start_id] = 0.0;

    // Валидация на наличие отрицательных весов во всем графе
    for (const auto& u : vertices) {
        for (const auto& edge : graph.getNeighbors(u)) {
            if (edge.weight < 0.0) {
                throw NegativeWeightException(
                    "Dijkstra cannot process negative weights. Found edge to "
                    + edge.target_id + " with weight "
                    + std::to_string(edge.weight));
            }
        }
    }

    // Очередь пар: <расстояние, vertex_id>
    using DistPair = std::pair<double, std::string>;
    std::priority_queue<DistPair,
                        std::vector<DistPair>,
                        std::greater<DistPair>> pq;

    pq.push({0.0, start_id});

    while (!pq.empty()) {
        double d = pq.top().first;
        std::string u = pq.top().second;
        pq.pop();

        if (d > result.distances[u]) continue;

        for (const auto& edge : graph.getNeighbors(u)) {
            std::string v = edge.target_id;
            double weight = edge.weight;

            if (result.distances[u] + weight < result.distances[v]) {
                result.distances[v] = result.distances[u] + weight;
                result.predecessors[v] = u;
                pq.push({result.distances[v], v});
            }
        }
    }

    return result;
}

// 2. Алгоритм BELLMAN-FORD
ShortestPathResult GraphAlgorithms::bellmanFord(
    const DirectedWeightedGraph& graph,
    const std::string& start_id) {

    if (!graph.hasVertex(start_id)) {
        throw VertexNotFoundException(
            "Start vertex for Bellman-Ford not found: " + start_id);
    }

    ShortestPathResult result;
    auto vertices = graph.getAllVertices();

    for (const auto& v : vertices) {
        result.distances[v] = INF;
        result.predecessors[v] = "";
    }
    result.distances[start_id] = 0.0;

    size_t num_vertices = vertices.size();

    // Релаксация ребер (V - 1) раз
    for (size_t i = 0; i < num_vertices - 1; ++i) {
        for (const auto& u : vertices) {
            if (result.distances[u] == INF) continue;

            for (const auto& edge : graph.getNeighbors(u)) {
                std::string v = edge.target_id;
                double weight = edge.weight;

                if (result.distances[u] + weight < result.distances[v]) {
                    result.distances[v] = result.distances[u] + weight;
                    result.predecessors[v] = u;
                }
            }
        }
    }

    // Проверка на наличие отрицательных циклов
    for (const auto& u : vertices) {
        if (result.distances[u] == INF) continue;

        for (const auto& edge : graph.getNeighbors(u)) {
            std::string v = edge.target_id;
            double weight = edge.weight;

            if (result.distances[u] + weight < result.distances[v]) {
                throw NegativeCycleException(
                    "Graph contains a negative weight cycle reachable from "
                    + start_id);
            }
        }
    }

    return result;
}

// 3. Волновой алгоритм (BFS для невзвешенного поиска)
std::vector<std::string> GraphAlgorithms::waveAlgorithm(
    const DirectedWeightedGraph& graph,
    const std::string& start_id,
    const std::string& end_id) {

    if (!graph.hasVertex(start_id)) {
        throw VertexNotFoundException(
            "Start vertex for Wave algorithm not found: " + start_id);
    }
    if (!graph.hasVertex(end_id)) {
        throw VertexNotFoundException(
            "Target vertex for Wave algorithm not found: " + end_id);
    }

    std::map<std::string, std::string> predecessors;
    std::map<std::string, bool> visited;

    for (const auto& v : graph.getAllVertices()) {
        visited[v] = false;
        predecessors[v] = "";
    }

    std::queue<std::string> q;
    q.push(start_id);
    visited[start_id] = true;

    bool target_found = false;

    while (!q.empty()) {
        std::string u = q.front();
        q.pop();

        if (u == end_id) {
            target_found = true;
            break;
        }

        for (const auto& edge : graph.getNeighbors(u)) {
            if (!visited[edge.target_id]) {
                visited[edge.target_id] = true;
                predecessors[edge.target_id] = u;
                q.push(edge.target_id);
            }
        }
    }

    if (!target_found) {
        throw PathNotFoundException(
            "No path exists between " + start_id + " and " + end_id);
    }

    std::vector<std::string> path;
    std::string current = end_id;
    while (!current.empty()) {
        path.push_back(current);
        current = predecessors[current];
    }
    std::reverse(path.begin(), path.end());
    return path;
}

} // namespace graph_project
