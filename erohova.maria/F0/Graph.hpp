#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <stack>
#include <cstddef>

class Graph {
private:
    size_t vertex_count;
    std::vector<std::vector<int>> adj_list;

    void dfs_directed_util(int vertex, std::vector<bool>& visited) const;
    void dfs_undirected_util(int vertex, std::vector<bool>& visited, std::vector<std::vector<int>>& undirected_adj) const;
    bool topo_sort_util(int vertex, std::vector<int>& state, std::stack<int>& finish_stack) const;

public:
    Graph(size_t vertices);

    void add_edge(int from, int to);
    bool has_vertex(int vertex) const;
    bool has_edge(int from, int to) const;
    void remove_vertex(int vertex);

    void dfs_directed() const;
    void dfs_undirected() const;
    void topological_sort() const;
};

#endif // GRAPH_HPP
