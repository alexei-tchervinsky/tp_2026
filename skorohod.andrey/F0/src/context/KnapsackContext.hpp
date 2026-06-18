#ifndef KNAPSACK_CONTEXT_HPP
#define KNAPSACK_CONTEXT_HPP

#include "../core/KnapsackInstance.hpp"
#include "../solvers/Solver.hpp"

class KnapsackContext
{
private:
    const KnapsackInstance* instance_ = nullptr;
    Solver* solver_ = nullptr;
public:
    KnapsackContext();
    KnapsackContext(const KnapsackInstance&, Solver&);
    ~KnapsackContext() = default;
    void setInstance(const KnapsackInstance&);
    void setSolver(Solver&);
    bool isReady() const;
    KnapsackSolution execute();
};

#endif
