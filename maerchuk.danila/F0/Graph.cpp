#include "Graph.hpp"
#include "GraphExceptions.hpp"
#include <algorithm>
#include <cmath>

namespace graph_project {

void DirectedWeightedGraph::addVertex(const std::string& vertex_id) {
    if (hasVertex(vertex_id)) {
        throw DuplicateVertexException("Vertex already exists: " + vertex_id);
    }
    adjacency_list_[vertex_id] = std::vector<Edge>();
}

void DirectedWeightedGraph::removeVertex(const std::string& vertex_id) {
    if (!hasVertex(vertex_id)) {
        throw VertexNotFoundException("Cannot remove non-existing vertex: " + vertex_id);
    }

    adjacency_list_.erase(vertex_id);

    for (auto& pair : adjacency_list_) {
        auto& edges = pair.second;
        edges.erase(
            std::remove_if(edges.begin(), edges.end(),
                [&vertex_id](const Edge& edge) { return edge.target_id == vertex_id; }),
            edges.end()
        );
    }
}

void DirectedWeightedGraph::addEdge(const std::string& from_id, const std::string& to_id, double weight) {
    // Автоматическая защита: проверяем некорректный ввод до модификации графа
    if (std::isnan(weight) || std::isinf(weight)) {
        throw InvalidWeightException("Edge weight cannot be NaN or Infinite");
    }
    if (!hasVertex(from_id)) {
        throw VertexNotFoundException("Source vertex not found: " + from_id);
    }
    if (!hasVertex(to_id)) {
        throw VertexNotFoundException("Target vertex not found: " + to_id);
    }

    for (auto& edge : adjacency_list_[from_id]) {
        if (edge.target_id == to_id) {
            edge.weight = weight;
            return;
        }
    }
    adjacency_list_[from_id].emplace_back(to_id, weight);
}

void DirectedWeightedGraph::removeEdge(const std::string& from_id, const std::string& to_id) {
    if (!hasVertex(from_id)) {
        throw VertexNotFoundException("Source vertex not found: " + from_id);
    }

    auto& edges = adjacency_list_[from_id];
    auto it = std::find_if(edges.begin(), edges.end(),
        [&to_id](const Edge& edge) { return edge.target_id == to_id; });

    if (it != edges.end()) {
        edges.erase(it);
    }
}

bool DirectedWeightedGraph::hasVertex(const std::string& vertex_id) const {
    return adjacency_list_.find(vertex_id) != adjacency_list_.end();
}

bool DirectedWeightedGraph::hasEdge(const std::string& from_id, const std::string& to_id) const {
    if (!hasVertex(from_id)) return false;

    const auto& edges = adjacency_list_.at(from_id);
    return std::any_of(edges.begin(), edges.end(),
        [&to_id](const Edge& edge) { return edge.target_id == to_id; });
}

bool DirectedWeightedGraph::isEmpty() const {
    return adjacency_list_.empty();
}

const std::vector<Edge>& DirectedWeightedGraph::getNeighbors(const std::string& vertex_id) const {
    auto it = adjacency_list_.find(vertex_id);
    if (it == adjacency_list_.end()) {
        throw VertexNotFoundException("Vertex not found to get neighbors: " + vertex_id);
    }
    return it->second;
}

std::vector<std::string> DirectedWeightedGraph::getAllVertices() const {
    std::vector<std::string> vertices;
    for (const auto& pair : adjacency_list_) {
        vertices.push_back(pair.first);
    }
    return vertices;
}

} // namespace graph_project
