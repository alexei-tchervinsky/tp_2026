#ifndef CONSOLE_PRINTER_HPP
#define CONSOLE_PRINTER_HPP

#include "../core/KnapsackSolution.hpp"
#include "../core/KnapsackInstance.hpp"
#include <string>

class ConsolePrinter
{
public:
    static void printSolution(const KnapsackSolution& solution, const KnapsackInstance& instance);

    static void printHeader(const std::string& title);

    static void printSeparator();

    static void printResultSummary(const std::string& solverName, int value, int weight, double timeMs);
};

#endif
