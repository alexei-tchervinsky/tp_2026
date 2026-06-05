#ifndef GRAPH_EXCEPTIONS_HPP
#define GRAPH_EXCEPTIONS_HPP

#include <stdexcept>
#include <string>

namespace graph_project {

class VertexNotFoundException : public std::runtime_error {
public:
    explicit VertexNotFoundException(const std::string& message)
        : std::runtime_error("Vertex Error: " + message) {}
};

class DuplicateVertexException : public std::runtime_error {
public:
    explicit DuplicateVertexException(const std::string& message)
        : std::runtime_error("Vertex Error: " + message) {}
};

class PathNotFoundException : public std::runtime_error {
public:
    explicit PathNotFoundException(const std::string& message)
        : std::runtime_error("Routing Error: " + message) {}
};

class NegativeCycleException : public std::runtime_error {
public:
    explicit NegativeCycleException(const std::string& message)
        : std::runtime_error("Algorithm Error: " + message) {}
};

class NegativeWeightException : public std::runtime_error {
public:
    explicit NegativeWeightException(const std::string& message)
        : std::runtime_error("Validation Error: " + message) {}
};

class InvalidWeightException : public std::runtime_error {
public:
    explicit InvalidWeightException(const std::string& message)
        : std::runtime_error("Validation Error: " + message) {}
};

} // namespace graph_project

#endif // GRAPH_EXCEPTIONS_HPP
