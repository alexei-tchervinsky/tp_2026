#include "KnapsackInstance.hpp"

KnapsackInstance::KnapsackInstance(size_t cap):
items_(),
capacity_(cap)
{}

void KnapsackInstance::addItem(const Item& it)
{
    items_.push_back(it);
}

const std::vector<Item>& KnapsackInstance::getItems() const
{
    return items_;
}

int KnapsackInstance::getCapacity() const
{
    return capacity_;
}

size_t KnapsackInstance::getItemCount() const
{
    return items_.size();
}
