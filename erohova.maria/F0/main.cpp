#include "Graph.hpp"
#include <iostream>

int main() {
    try {
        Graph g(6);

        g.add_edge(5, 2);
        g.add_edge(5, 0);
        g.add_edge(4, 0);
        g.add_edge(4, 1);
        g.add_edge(2, 3);
        g.add_edge(3, 1);

        std::cout << "Checking for an arc 5->2: " << (g.has_edge(5, 2) ? "Yes" : "No") << "\n";
        std::cout << "Checking for an arc 2->5: " << (g.has_edge(2, 5) ? "Yes" : "No") << "\n";

        g.dfs_directed();
        g.dfs_undirected();
        g.topological_sort();

        std::cout << "\n--- Let's add a loop to check the validation ---\n";
        g.add_edge(1, 5);
        g.topological_sort();

    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}
