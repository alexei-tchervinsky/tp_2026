#ifndef BRUTE_FORCE_SOLVER_HPP
#define BRUTE_FORCE_SOLVER_HPP

#include "Solver.hpp"

class BruteForceSolver : public Solver {
public:
    KnapsackSolution solve(const KnapsackInstance& instance) override;
    const char* getName() const override { return "Brute Force"; }
};

#endif
