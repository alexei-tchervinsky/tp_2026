#ifndef GREEDY_SOLVER_HPP
#define GREEDY_SOLVER_HPP

#include "Solver.hpp"


class GreedySolverDensity : public Solver
{
public:
    KnapsackSolution solve(const KnapsackInstance& instance) override;
    const char* getName() const override { return "Greedy by density"; }
private:
    struct ItemData
    {
        Item item;
        int originalIndex;
        bool operator>(const ItemData& other) const { return item.getDensity() > other.item.getDensity(); }
        bool operator<(const ItemData& other) const { return item.getDensity() < other.item.getDensity(); }
    };
};

class GreedySolverValue : public Solver
{
public:
    KnapsackSolution solve(const KnapsackInstance& instance) override;
    const char* getName() const override { return "Greedy by value"; }
private:
    struct ItemData
    {
        Item item;
        int originalIndex;
        bool operator>(const ItemData& other) const { return item.getValue() > other.item.getValue(); }
        bool operator<(const ItemData& other) const { return item.getValue() < other.item.getValue(); }
    };
};

class GreedySolverWeigth : public Solver
{
public:
    KnapsackSolution solve(const KnapsackInstance& instance) override;
    const char* getName() const override { return "Greedy by weigth"; }
private:
    struct ItemData
    {
        Item item;
        int originalIndex;
        bool operator>(const ItemData& other) const { return item.getWeight() < other.item.getWeight(); }
        bool operator<(const ItemData& other) const { return item.getWeight() > other.item.getWeight(); }
    };
};
#endif
