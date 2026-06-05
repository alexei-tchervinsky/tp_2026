#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <map>
#include <string>

namespace graph_project {

struct Edge {
    std::string target_id;
    double weight;

    Edge(const std::string& target, double w) : target_id(target), weight(w) {}
};

class DirectedWeightedGraph {
public:
    DirectedWeightedGraph() = default;
    ~DirectedWeightedGraph() = default;

    void addVertex(const std::string& vertex_id);
    void removeVertex(const std::string& vertex_id);
    void addEdge(const std::string& from_id, const std::string& to_id, double weight);
    void removeEdge(const std::string& from_id, const std::string& to_id);

    bool hasVertex(const std::string& vertex_id) const;
    bool hasEdge(const std::string& from_id, const std::string& to_id) const;
    bool isEmpty() const;

    const std::vector<Edge>& getNeighbors(const std::string& vertex_id) const;
    std::vector<std::string> getAllVertices() const;

private:
    std::map<std::string, std::vector<Edge>> adjacency_list_;
};

} // namespace graph_project

#endif // GRAPH_HPP
