#include "KnapsackContext.hpp"
#include <stdexcept>

KnapsackContext::KnapsackContext()
{}

KnapsackContext::KnapsackContext(const KnapsackInstance& inst, Solver& sol):
instance_(&inst),
solver_(&sol)
{}

void KnapsackContext::setInstance(const KnapsackInstance& inst)
{
    instance_ = &inst;
}

void KnapsackContext::setSolver(Solver& sol)
{
    solver_ = &sol;
}

bool KnapsackContext::isReady() const
{
    return (instance_ != nullptr) && (solver_ != nullptr);
}

KnapsackSolution KnapsackContext::execute()
{
    if (!isReady())
    {
        throw std::logic_error("Instance or solver not set");
    }

    return solver_->solve(*instance_);
}
