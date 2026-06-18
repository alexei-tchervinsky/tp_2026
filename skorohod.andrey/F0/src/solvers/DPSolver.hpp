#ifndef DP_SOLVER_HPP
#define DP_SOLVER_HPP

#include "Solver.hpp"

class DPSolver : public Solver {
public:
    KnapsackSolution solve(const KnapsackInstance& instance) override;
    const char* getName() const override { return "Dynamic Programming"; }
};

#endif
