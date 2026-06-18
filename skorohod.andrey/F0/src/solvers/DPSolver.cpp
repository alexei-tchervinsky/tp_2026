#include "DPSolver.hpp"
#include <vector>
#include <stdexcept>

template<typename T>
T max(T a, T b)
{
    return (a > b) ? a : b;
}

KnapsackSolution DPSolver::solve(const KnapsackInstance& instance)
{
    const std::vector<Item>& items = instance.getItems();
    int n = instance.getItemCount();
    int capacity = instance.getCapacity();

    if (n == 0 || capacity <= 0)
    {
        return KnapsackSolution();
    }

    std::vector< std::vector<int> > dpTable;
    dpTable.resize(n + 1);
    for (int i = 0; i <= n; ++i)
    {
        dpTable[i].resize(capacity + 1, 0);
    }

    for (int i = 1; i <= n; ++i)
    {
        int weight = items[i - 1].getWeight();
        int value  = items[i - 1].getValue();
        for (int w = 0; w <= capacity; ++w)
        {
            if (weight <= w)
            {
                dpTable[i][w] = max(dpTable[i - 1][w], dpTable[i - 1][w - weight] + value);
            }
            else
            {
                dpTable[i][w] = dpTable[i - 1][w];
            }
        }
    }

    KnapsackSolution solution;
    int w = capacity;
    for (int i = n; i > 0; --i)
    {
        int weight = items[i - 1].getWeight();
        int value  = items[i - 1].getValue();
        if (dpTable[i][w] != dpTable[i - 1][w])
        {
            solution.addItem(static_cast<size_t>(i - 1), weight, value);
            w -= weight;
        }
    }

    return solution;
}
