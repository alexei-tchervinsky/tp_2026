#ifndef BNB_SOLVER_HPP
#define BNB_SOLVER_HPP

#include "Solver.hpp"
#include <queue>
#include <vector>

class BnBSolver : public Solver
{
public:
    KnapsackSolution solve(const KnapsackInstance& instance) override;
    const char* getName() const override { return "Branch and Bound"; }
private:
    struct ItemData
    {
        Item item;
        int originalIndex;
        bool operator>(const ItemData& other) const { return item.getDensity() > other.item.getDensity(); }
        bool operator<(const ItemData& other) const { return item.getDensity() < other.item.getDensity(); }

    };

    struct Node
    {
        int level;
        int weight;
        int value;
        double bound;
        std::vector<int> taken;

        bool operator>(const Node& other) const { return bound > other.bound; }
        bool operator<(const Node& other) const { return bound < other.bound; }
        bool operator>=(const Node& other) const { return bound >= other.bound; }
    };

    std::vector<ItemData> sortedItems;
    int capacity;
    int bestValue;
    std::vector<int> bestTaken;

    double computeBound(int level, int currentWeight, int currentValue) const;

};

#endif
