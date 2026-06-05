#ifndef GRAPH_ALGORITHMS_HPP
#define GRAPH_ALGORITHMS_HPP

#include "Graph.hpp"
#include <map>
#include <string>
#include <vector>
#include <limits>

namespace graph_project {

struct ShortestPathResult {
    std::map<std::string, double> distances;
    std::map<std::string, std::string> predecessors;

    std::vector<std::string> reconstructPath(const std::string& target) const;
};

class GraphAlgorithms {
public:
    static constexpr double INF = std::numeric_limits<double>::infinity();

    static ShortestPathResult dijkstra(const DirectedWeightedGraph& graph, const std::string& start_id);
    static ShortestPathResult bellmanFord(const DirectedWeightedGraph& graph, const std::string& start_id);

    static std::vector<std::string> waveAlgorithm(const DirectedWeightedGraph& graph,
                                                  const std::string& start_id,
                                                  const std::string& end_id);
};

} // namespace graph_project

#endif // GRAPH_ALGORITHMS_HPP
