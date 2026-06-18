#include "KnapsackSolution.hpp"

KnapsackSolution::KnapsackSolution():
totalValue_(0),
totalWeight_(0)
{}

KnapsackSolution::KnapsackSolution(KnapsackSolution&& other) noexcept :
selectedIndices_(std::move(other.selectedIndices_)),
totalValue_(other.totalValue_),
totalWeight_(other.totalWeight_)
{}

KnapsackSolution& KnapsackSolution::operator=(KnapsackSolution&& other) noexcept
{
    if (this != &other)
    {
        selectedIndices_ = std::move(other.selectedIndices_);
        totalValue_ = other.totalValue_;
        totalWeight_ = other.totalWeight_;
        other.totalValue_ = 0;
        other.totalWeight_ = 0;
    }
    return *this;
}

void KnapsackSolution::addItem(size_t index, int weight, int value)
{
    selectedIndices_.push_back(index);
    totalValue_ += value;
    totalWeight_ += weight;
}

int KnapsackSolution::getTotalValue() const
{
    return totalValue_;
}

int KnapsackSolution::getTotalWeight() const
{
    return totalWeight_;
}

const std::vector<size_t>& KnapsackSolution::getSelectedIndices() const
{
    return selectedIndices_;
}

void KnapsackSolution::setTotalValue(int v)
{
    totalValue_ = v;
}

void KnapsackSolution::setTotalWeight(int w)
{
    totalWeight_ = w;
}
