#include "BruteForceSolver.hpp"
#include <vector>
#include <stdexcept>

KnapsackSolution BruteForceSolver::solve(const KnapsackInstance& instance)
{
    const std::vector<Item>& items = instance.getItems();
    int n = instance.getItemCount();
    int capacity = instance.getCapacity();

    if (n == 0) return KnapsackSolution();

    std::vector<char> mask(n, 0);

    int bestValue = 0;
    std::vector<char> bestMask;

    bool finished = false;
    while (!finished)
    {
        int weight = 0;
        int value = 0;
        for (int i = 0; i < n; ++i)
        {
            if (mask[i])
            {
                weight += items[i].getWeight();
                value += items[i].getValue();
            }
        }

        if (weight <= capacity && value > bestValue)
        {
            bestValue = value;
            bestMask = mask;
        }

        int idx = 0;
        while (idx < n && mask[idx] == 1)
        {
            mask[idx] = 0;
            ++idx;
        }
        if (idx == n) finished = true;
        else mask[idx] = 1;
    }

    KnapsackSolution solution;
    for (int i = 0; i < n; ++i)
    {
        if (bestMask[i]) solution.addItem(static_cast<size_t>(i), items[i].getWeight(), items[i].getValue());
    }
    return solution;
}
