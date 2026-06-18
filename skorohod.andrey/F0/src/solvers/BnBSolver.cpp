#include "BnBSolver.hpp"
#include <utility>
#include <algorithm>

double BnBSolver::computeBound(int level, int currentWeight, int currentValue) const
{
    int n = sortedItems.size();
    double bound = currentValue;
    int remainingWeight = capacity - currentWeight;
    int i = level;
    while (i < n && sortedItems[i].item.getWeight() <= remainingWeight)
    {
        bound += sortedItems[i].item.getValue();
        remainingWeight -= sortedItems[i].item.getWeight();
        ++i;
    }
    if (i < n && remainingWeight > 0)
    {
        bound += sortedItems[i].item.getValue() * (static_cast<double>(remainingWeight) / sortedItems[i].item.getWeight());
    }
    return bound;
}

KnapsackSolution BnBSolver::solve(const KnapsackInstance& instance)
{
    const std::vector<Item>& origItems = instance.getItems();
    int n = origItems.size();
    capacity = instance.getCapacity();

    if (n == 0 || capacity <= 0) return KnapsackSolution();

    sortedItems.clear();
    sortedItems.reserve(n);
    for (int i = 0; i < n; ++i)
    {
        ItemData data;
        data.item = origItems[i];
        data.originalIndex = i;
        sortedItems.push_back(data);
    }
    std::sort(sortedItems.begin(), sortedItems.end());
    std::reverse(sortedItems.begin(), sortedItems.end());

    bestValue = -1;
    bestTaken.clear();

    std::priority_queue<Node> pq;
    Node root;
    root.level = 0;
    root.weight = 0;
    root.value = 0;
    root.bound = computeBound(0, 0, 0);
    root.taken.clear();
    pq.push(std::move(root));

    while (!pq.empty())
    {
        Node current = std::move(pq.top());
        pq.pop();

        if (current.bound <= bestValue)
            continue;

        if (current.level == n)
        {
            if (current.value > bestValue)
            {
                bestValue = current.value;
                bestTaken = std::move(current.taken);
            }
            continue;
        }

        const ItemData& itemData = sortedItems[current.level];

        Node notTake;
        notTake.level = current.level + 1;
        notTake.weight = current.weight;
        notTake.value = current.value;
        notTake.taken = current.taken;
        notTake.bound = computeBound(notTake.level, notTake.weight, notTake.value);
        if (notTake.bound > bestValue) pq.push(std::move(notTake));

        int newWeight = current.weight + itemData.item.getWeight();
        if (newWeight <= capacity)
        {
            Node take;
            take.level = current.level + 1;
            take.weight = newWeight;
            take.value = current.value + itemData.item.getValue();
            take.taken = std::move(current.taken);
            take.taken.push_back(itemData.originalIndex);
            take.bound = computeBound(take.level, take.weight, take.value);
            if (take.bound > bestValue) pq.push(std::move(take));
        }
    }

    KnapsackSolution solution;
    for (size_t i = 0; i < bestTaken.size(); ++i)
    {
        int idx = bestTaken[i];
        solution.addItem(static_cast<size_t>(idx), origItems[idx].getWeight(), origItems[idx].getValue());
    }
    return solution;
}
