#include "Graph.hpp"
#include <iostream>
#include <stdexcept>

Graph::Graph(size_t vertices) : vertex_count(vertices), adj_list(vertices) {}

void Graph::add_edge(int from, int to) {
    if (!has_vertex(from) || !has_vertex(to)) {
        throw std::invalid_argument("Vertex index out of bounds");
    }
    if (!has_edge(from, to)) {
        adj_list[from].push_back(to);
    }
}

bool Graph::has_vertex(int vertex) const {
    return vertex >= 0 && static_cast<size_t>(vertex) < vertex_count;
}

bool Graph::has_edge(int from, int to) const {
    if (!has_vertex(from) || !has_vertex(to)) return false;
    for (size_t i = 0; i < adj_list[from].size(); ++i) {
        if (adj_list[from][i] == to) return true;
    }
    return false;
}

void Graph::remove_vertex(int vertex) {
    if (!has_vertex(vertex)) {
        throw std::invalid_argument("Vertex does not exist");
    }

    adj_list[vertex].clear();

    for (size_t i = 0; i < vertex_count; ++i) {
        std::vector<int>& edges = adj_list[i];
        std::vector<int> updated_edges;
        for (size_t j = 0; j < edges.size(); ++j) {
            if (edges[j] != vertex) {
                updated_edges.push_back(edges[j]);
            }
        }
        edges = updated_edges;
    }
    std::cout << "[Info]: Top " << vertex << " isolated (connected edges removed).\n";
}

void Graph::dfs_directed_util(int vertex, std::vector<bool>& visited) const {
    visited[vertex] = true;
    std::cout << vertex << " ";

    for (size_t i = 0; i < adj_list[vertex].size(); ++i) {
        int neighbor = adj_list[vertex][i];
        if (!visited[neighbor]) {
            dfs_directed_util(neighbor, visited);
        }
    }
}

void Graph::dfs_directed() const {
    std::vector<bool> visited(vertex_count, false);
    std::cout << "DFS of a directed graph: ";
    for (size_t i = 0; i < vertex_count; ++i) {
        if (!visited[i]) {
            dfs_directed_util(static_cast<int>(i), visited);
        }
    }
    std::cout << "\n";
}

void Graph::dfs_undirected_util(int vertex, std::vector<bool>& visited, std::vector<std::vector<int>>& undirected_adj) const {
    visited[vertex] = true;
    std::cout << vertex << " ";

    for (size_t i = 0; i < undirected_adj[vertex].size(); ++i) {
        int neighbor = undirected_adj[vertex][i];
        if (!visited[neighbor]) {
            dfs_undirected_util(neighbor, visited, undirected_adj);
        }
    }
}

void Graph::dfs_undirected() const {
    std::vector<std::vector<int>> undirected_adj(vertex_count);
    for (size_t u = 0; u < vertex_count; ++u) {
        for (size_t i = 0; i < adj_list[u].size(); ++i) {
            int v = adj_list[u][i];
            undirected_adj[u].push_back(v);
            undirected_adj[v].push_back(static_cast<int>(u));
        }
    }

    std::vector<bool> visited(vertex_count, false);
    std::cout << "DFS of an undirected graph: ";
    for (size_t i = 0; i < vertex_count; ++i) {
        if (!visited[i]) {
            dfs_undirected_util(static_cast<int>(i), visited, undirected_adj);
        }
    }
    std::cout << "\n";
}

bool Graph::topo_sort_util(int vertex, std::vector<int>& state, std::stack<int>& finish_stack) const {
    state[vertex] = 1;

    for (size_t i = 0; i < adj_list[vertex].size(); ++i) {
        int neighbor = adj_list[vertex][i];
        if (state[neighbor] == 1) {
            return false;
        }
        if (state[neighbor] == 0) {
            if (!topo_sort_util(neighbor, state, finish_stack)) {
                return false;
            }
        }
    }

    state[vertex] = 2;
    finish_stack.push(vertex);
    return true;
}

void Graph::topological_sort() const {
    std::vector<int> state(vertex_count, 0);
    std::stack<int> finish_stack;

    for (size_t i = 0; i < vertex_count; ++i) {
        if (state[i] == 0) {
            if (!topo_sort_util(static_cast<int>(i), state, finish_stack)) {
                std::cout << "Error: The graph contains a cycle! Topological sorting is not possible.\n";
                return;
            }
        }
    }

    std::cout << "Topological sorting: ";
    while (!finish_stack.empty()) {
        std::cout << finish_stack.top() << " ";
        finish_stack.pop();
    }
    std::cout << "\n";
}
