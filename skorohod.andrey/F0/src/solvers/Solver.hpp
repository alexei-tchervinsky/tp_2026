#ifndef SOLVER_HPP
#define SOLVER_HPP

#include "../core/KnapsackInstance.hpp"
#include "../core/KnapsackSolution.hpp"

class Solver {
public:
    virtual ~Solver() {}
    virtual KnapsackSolution solve(const KnapsackInstance& instance) = 0;
    virtual const char* getName() const = 0;
};

#endif
