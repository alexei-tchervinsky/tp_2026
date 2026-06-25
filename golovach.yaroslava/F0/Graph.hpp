#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <string>

class Graph
{
public:
    explicit Graph(int n);

    bool isEmpty() const;
    bool hasNode(int node) const;
    bool hasEdge(int from, int to) const;

    void addNode();
    void removeNode(int node);
    void addEdge(int from, int to, int weight = 1);
    int  removeEdge(int from, int to);

    void printDegrees() const;
    int  maxDegreeNode() const;
    void removeMultipleEdgesAndLoops();
    void findSourcesAndSinks() const;

    void printMatrix() const;

private:
    int nodeCount_;
    std::vector<std::vector<int>> matrix_;

    void validateNode(int node) const;
};

#endif // GRAPH_HPP
