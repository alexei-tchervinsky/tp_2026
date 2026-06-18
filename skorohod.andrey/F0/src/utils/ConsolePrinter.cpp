#include "ConsolePrinter.hpp"
#include <iostream>
#include <iomanip>

void ConsolePrinter::printSolution(const KnapsackSolution& solution, const KnapsackInstance& instance)
{
    const std::vector<size_t>& indices = solution.getSelectedIndices();
    const std::vector<Item>& items = instance.getItems();

    std::cout << "Selected items:\n";
    if (indices.empty())
    {
        std::cout << "  none\n";
    }
    else
    {
        for (size_t i = 0; i < indices.size(); ++i)
        {
            size_t idx = indices[i];
            std::cout << "  #" << idx << ": weight=" << items[idx].getWeight() << ", value=" << items[idx].getValue() << "\n";
        }
    }
    std::cout << "Total weight: " << solution.getTotalWeight() << "\n";
    std::cout << "Total value:  " << solution.getTotalValue() << "\n";
}

void ConsolePrinter::printHeader(const std::string& title)
{
    std::cout << "\n=== " << title << " ===\n";
}

void ConsolePrinter::printSeparator()
{
    std::cout << "----------------------------------------\n";
}

void ConsolePrinter::printResultSummary(const std::string& solverName, int value, int weight, double timeMs)
{
    std::cout << std::left << std::setw(25) << solverName
              << " value=" << std::setw(8) << value
              << " weight=" << std::setw(8) << weight
              << " time=" << std::setw(10) << std::fixed << std::setprecision(3) << timeMs << " ms\n";
}
