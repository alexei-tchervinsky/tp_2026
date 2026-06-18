#ifndef KNAPSACK_INSTANCE_HPP
#define KNAPSACK_INSTANCE_HPP

#include "Item.hpp"
#include <vector>

class KnapsackInstance
{
public:
    KnapsackInstance(size_t cap = 0);
    void addItem(const Item&);
    const std::vector<Item>& getItems() const;
    int getCapacity() const;
    size_t getItemCount() const;

private:
    std::vector<Item> items_;
    int capacity_;
};

#endif
