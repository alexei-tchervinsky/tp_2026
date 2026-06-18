#include "BacktrackingSolver.hpp"
#include <vector>
#include <stdexcept>

void BacktrackingSolver::backtrack(size_t idx, int currentWeight, int currentValue)
{
    if (currentValue + suffixSum[idx] <= bestValue_) return;
    const std::vector<Item>& items = inst_->getItems();
    size_t n = inst_->getItemCount();
    int capacity = inst_->getCapacity();

    if (idx == n)
    {
        if (currentValue > bestValue_)
        {
            bestValue_ = currentValue;
            bestTaken_ = currentTaken_;
        }
        return;
    }

    backtrack(idx + 1, currentWeight, currentValue);

    int weightItem = items[idx].getWeight();
    int valueItem  = items[idx].getValue();
    if (currentWeight + weightItem <= capacity)
    {
        currentTaken_.push_back(idx);
        backtrack(idx + 1, currentWeight + weightItem, currentValue + valueItem);
        currentTaken_.pop_back();
    }
}

KnapsackSolution BacktrackingSolver::solve(const KnapsackInstance& instance)
{
    inst_ = &instance;
    int n = instance.getItemCount();
    int capacity = instance.getCapacity();

    if (n == 0 || capacity <= 0) return KnapsackSolution();

    const std::vector<Item>& items = instance.getItems();
    suffixSum.resize(n + 1);
    suffixSum[n] = 0;
    for (int i = n - 1; i >= 0; --i)
    {
        suffixSum[i] = suffixSum[i + 1] + items[i].getValue();
    }

    bestValue_ = -1;
    bestTaken_.clear();
    currentTaken_.clear();

    backtrack(0, 0, 0);

    KnapsackSolution solution;
    for (size_t i = 0; i < bestTaken_.size(); ++i)
    {
        int idx = bestTaken_[i];
        solution.addItem(static_cast<size_t>(idx), items[idx].getWeight(), items[idx].getValue());
    }
    return solution;
}
