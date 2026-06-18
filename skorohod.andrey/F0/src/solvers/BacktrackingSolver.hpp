#ifndef BACKTRACKING_SOLVER_HPP
#define BACKTRACKING_SOLVER_HPP

#include "Solver.hpp"

class BacktrackingSolver : public Solver
{
public:
    KnapsackSolution solve(const KnapsackInstance& instance) override;
    const char* getName() const override { return "Backtracking"; }

private:
    const KnapsackInstance* inst_;
    int bestValue_;
    std::vector<size_t> bestTaken_;
    std::vector<size_t> currentTaken_;
    std::vector<int> suffixSum;

    void backtrack(size_t idx, int currentWeight, int currentValue);
};

#endif
