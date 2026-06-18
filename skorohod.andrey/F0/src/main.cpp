#include "core/KnapsackInstance.hpp"
#include "core/Item.hpp"
#include "solvers/BruteForceSolver.hpp"
#include "solvers/DPSolver.hpp"
#include "solvers/BacktrackingSolver.hpp"
#include "solvers/BnBSolver.hpp"
#include "solvers/GreedySolver.hpp"
#include "utils/FileReader.hpp"
#include "utils/ConsolePrinter.hpp"
#include "utils/Timer.hpp"
#include <iostream>
#include <string>
#include <stdexcept>

void runSolver(Solver& solver, const KnapsackInstance& instance)
{
    ConsolePrinter::printHeader(solver.getName());
    Timer timer;
    timer.start();
    KnapsackSolution solution = solver.solve(instance);
    timer.stop();
    ConsolePrinter::printSolution(solution, instance);
    std::cout << "Time: " << timer.elapsedMilliseconds() << " ms\n";
    ConsolePrinter::printSeparator();
}

int main(int argc, char* argv[])
{
    std::string filename;
    if (argc > 1)
        filename = argv[1];
    else
        filename = "data/test1.txt";

    KnapsackInstance instance;
    try
    {
        instance = FileReader::read(filename);
        std::cout << "Loaded instance from " << filename << "\n";
        std::cout << "Capacity: " << instance.getCapacity() << ", items: " << instance.getItemCount() << "\n";
        ConsolePrinter::printSeparator();
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error reading file: " << e.what() << "\n";
        return 1;
    }

    BruteForceSolver bruteSolver;
    DPSolver dpSolver;
    BacktrackingSolver backtrackSolver;
    BnBSolver bnbSolver;
    GreedySolverDensity gDSolver;
    GreedySolverValue gVSolver;
    GreedySolverWeigth gWSolver;

    if (instance.getItemCount() < 25) runSolver(bruteSolver, instance);
    runSolver(dpSolver, instance);
    if (instance.getItemCount() < 25) runSolver(backtrackSolver, instance);
    runSolver(bnbSolver, instance);
    runSolver(gDSolver, instance);
    runSolver(gVSolver, instance);
    runSolver(gWSolver, instance);

    return 0;
}
